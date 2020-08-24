#include "Airplane.h"
#include "Airline.h"
#include "Flight.h"
#include "Seat.h"
#include <QString>
#include <stdexcept>
using namespace std;

extern bool ISDATACHANGED;

void Airplane::attachFlight(Flight *f)
{
    if (f && !isFlightInList(f))
    {
        FlightItem::attachFlight(f);

        f->setAirplane(this);

//        ISDATACHANGED = true;
    }
}

void Airplane::setAirline(Airline *value)
{
    if (value)
    {
        FlightItem::setAirline(value);

        value->attachAirplane(this);

//        ISDATACHANGED = true;
    }
}

int Airplane::getNumOfSeats() const
{
    return numOfSeats;
}

void Airplane::setNumOfSeats(int value)
{
    if (value <= 0)
        throw invalid_argument("Invalid Value For Num Of Seats");
    numOfSeats = value;

    ISDATACHANGED = true;
}

QString Airplane::getSerial() const
{
    return serial;
}

void Airplane::setSerial(const QString &value)
{
    if (value == "")
        throw invalid_argument("Serial Is Empty!");
    serial = value;
    this->setSearchCode(value);

    ISDATACHANGED = true;
}

void Airplane::removeFlight(Flight * f)
{
    if(f && isFlightInList(f)){
        FlightItem::removeFlight(f);

        f->removeAirplane();

//        ISDATACHANGED = true;
    }
}

void Airplane::attachDoneFlight(Flight * f)
{
    if (f && !this->isDoneFlightInList(f) && isFlightInList(f))
    {
        FlightItem::attachDoneFlight(f);
//        ISDATACHANGED = true;
    }
}

void Airplane::removeDoneFlight(Flight *f)
{
    if(f && isDoneFlightInList(f) && isFlightInList(f)){
        FlightItem::removeDoneFlight(f);
//        ISDATACHANGED = true;
    }
}

bool Airplane::isFree(Flight * f) const
{
    if (this->numOfSeats < f->getCapacity())
        return false;

    return FlightItem::isFree(f);
}

void Airplane::createSeats(int rows, int cols)
{
    this->seats = new Seat* [rows];
    for (int i = 0; i < rows; i++)
    {
        this->seats[i] = new Seat[cols];
        for (int j = 0; j < cols; j++)
        {
            this->seats[i][j].setSeatInfo(i, j, this);
        }
    }
    this->setNumOfSeats(rows * cols);

}

Airplane::Airplane(const QString &serial, Airline *airline, int rows, int cols)
{
    this->setSerial(serial);
    this->setAirline(airline);

    this->num_of_rows = rows;
    this->num_of_cols = cols;

    this->createSeats(rows, cols);

}

Airplane::Airplane(QString & str_data)
{
    QStringList str_list = str_data.split('|');
    this->setSerial(str_list[0]);
    this->setAirline(Recorder<Airline>::getInstance()->searchByCode(str_list[1]));


    int rows = str_list[2].toInt();
    int cols = str_list[3].toInt();


    this->num_of_rows = rows;
    this->num_of_cols = cols;

    this->createSeats(rows, cols);

    QStringList flights = str_list[4].split('/', Qt::SkipEmptyParts);

    foreach (QString s, flights)
    {
        this->attachFlight(this->getAirline()->searchFlightByCode(s));
    }
}

Airplane::~Airplane()
{
    for (int i = 0; i < this->num_of_rows; i++)
    {
        delete [] this->seats[i];
        this->seats[i] = nullptr;
    }

    delete [] this->seats;
    this->seats = nullptr;

    if (getAirline())
        this->getAirline()->removeAirplane(this);

    foreach (Flight * f, this->getFlightList())
    {
        if (f)
            f->removeAirplane();
    }

    ISDATACHANGED = true;
}

QString Airplane::get_data()
{
    QString str = this->getSearchCode() + "|" +
            (this->getAirline() ? this->getAirline()->getSearchCode() : "") + "|" +
            QString::number(this->num_of_rows) + "|" +
            QString::number(this->num_of_cols) + "|" ;

    for (int i = 0; i < this->flightListSize() && this->getFlightList()[i]; i++)
    {
        if (i == this->flightListSize() - 1)
            str += this->getFlightList()[i]->getSearchCode();
        else
            str += this->getFlightList()[i]->getSearchCode() + "/";
    }

    str += "|";

    for (int i = 0; i < this->DoneFlightListSize() && this->getDoneFlightList()[i]; i++)
    {
        if (i == this->DoneFlightListSize() - 1)
            str += this->getDoneFlightList()[i]->getSearchCode();
        else
            str += this->getDoneFlightList()[i]->getSearchCode() + "/";
    }

    str += "\n";

    return str;
}
int Airplane::getRowCount() const{return this->num_of_rows;}
int Airplane::getcolumnCount() const{return this->num_of_cols; }
Seat * Airplane::getSeat(int r,int c) const{
    return &seats[r][c];
}








