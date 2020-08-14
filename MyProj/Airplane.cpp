#include "Airplane.h"
#include "Airline.h"
#include "Flight.h"
#include "Seat.h"
#include <QString>
#include <stdexcept>
using namespace std;

void Airplane::attachFlight(Flight *f)
{
    if (f && !isFlightInList(f))
    {
        this->list_of_flights.push_back(f);

        f->setAirplane(this);
    }
//    Recorder<Airplane>::getInstance()->updateFile(this);
}

Airline *Airplane::getAirline() const
{
    return this->airline;
}

void Airplane::setAirline(Airline *value)
{
    if (value)
    {
        this->airline = value;

        value->attachAirplane(this);
    }
//    Recorder<Airplane>::getInstance()->updateFile(this);
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
//    Recorder<Airplane>::getInstance()->updateFile(this);
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
//    this->search_code = value;
    this->setSearchCode(value);
    //    Recorder<Airplane>::getInstance()->updateFile(this);
}

void Airplane::removeFlight(Flight * f)
{
    this->list_of_flights.removeOne(f);
}

bool Airplane::isFree(Flight * f)
{
    if (this->numOfSeats < f->getNumOfPassengers())
        return false;

    if(isFlightInList(f))
    {
        return false;
    }
    if(prevFlight(f)==f || nextFlight(f)==f)
    {
        return false;
    }
    if(prevFlight(f)==nullptr&&nextFlight(f)==nullptr)
    {
        return true;
    }
    else if(prevFlight(f)==nullptr)
    {
        if(nextFlight(f)->getSource()==f->getDestination())return true;
        else if(f->getDateTimeDeparture().secsTo(nextFlight(f)->getDateTimeDeparture())>86400)return true;
        else return false;
    }
    else if(nextFlight(f)==nullptr)
    {
        if(prevFlight(f)->getDestination()==f->getSource())return true;
        else if(prevFlight(f)->getDateTimeDeparture().secsTo(f->getDateTimeDeparture())>86400)return true;
        else return false;
    }

    if(prevFlight(f)->getDestination()==f->getSource()&&f->getDestination()==nextFlight(f)->getSource()){
        return true;
    }
    else if((f->getDateTimeDeparture().secsTo(nextFlight(f)->getDateTimeDeparture())>24 * 60 * 60 &&
            f->getDestination() != nextFlight(f)->getSource()) ||
            ((prevFlight(f)->getDateTimeDeparture().secsTo(f->getDateTimeDeparture())>24 * 60 * 60) &&
             f->getSource() == prevFlight(f)->getDestination()))
    {
        return true;
    }
    else{
        return false;
    }
}

Flight* Airplane::nextFlight(Flight * f){
    if(list_of_flights.size()==0){return nullptr;}
    Flight* next = nullptr;
    for (int i = 0; i < this->list_of_flights.size(); i++)
    {
        if(f->getDateTimeDeparture()<this->list_of_flights.at(i)->getDateTimeDeparture()){
            next=list_of_flights.at(i);
        }
    }
    for (int i = 0; i < this->list_of_flights.size(); i++)
    {
        if (next)
        {
            if(f->getDateTimeDeparture()<this->list_of_flights.at(i)->getDateTimeDeparture() &&
                  next->getDateTimeDeparture()>this->list_of_flights.at(i)->getDateTimeDeparture()  )
            {
                next=list_of_flights.at(i);
            }
        }
    }

    if (next)
    {
        if(next->getDateTimeDeparture()<=f->getDateTimeArrival()){return f; }
    }
    return next;
}

Flight* Airplane::prevFlight(Flight * f){
    if(list_of_flights.size()==0){return nullptr;}
    Flight* prev = nullptr;
    for (int i = 0; i < this->list_of_flights.size(); i++)
    {
        if(f->getDateTimeDeparture()>this->list_of_flights.at(i)->getDateTimeDeparture()){
            prev=list_of_flights.at(i);
        }
    }
    for (int i = 0; i < this->list_of_flights.size(); i++)
    {
        if (prev)
        {
            if(f->getDateTimeDeparture()>this->list_of_flights.at(i)->getDateTimeDeparture() &&
                  prev->getDateTimeDeparture()<this->list_of_flights.at(i)->getDateTimeDeparture()  )
            {
                prev=list_of_flights.at(i);
            }
        }
    }

    if (prev)
    {
        if(prev->getDateTimeArrival()>=f->getDateTimeDeparture()){return f; }
    }
    return prev;
}

bool Airplane::isFlightInList(Flight * f)
{
    foreach (Flight* fl, this->list_of_flights)
    {
        if (fl == f)
            return true;
    }
    return false;
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
    : airline(nullptr)
{
    QStringList str_list = str_data.split('|');
    this->setSerial(str_list[0]);
    this->setAirline(Recorder<Airline>::getInstance()->searchByCode(str_list[1]));


    //QStringList product_date = str_list[2].split('/', Qt::SkipEmptyParts);
    //this->setProductDate(product_date[2].toInt(), product_date[0].toInt(), product_date[1].toInt());

    int rows = str_list[2].toInt();
    int cols = str_list[3].toInt();



    this->num_of_rows = rows;
    this->num_of_cols = cols;

    this->createSeats(rows, cols);

    QStringList flights = str_list[4].split('/', Qt::SkipEmptyParts);

    foreach (QString s, flights)
    {
        this->attachFlight(this->airline->searchFlightByCode(s));
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
}

QString Airplane::get_data()
{
    QString str = this->getSearchCode() + "|" +
            (this->airline ? this->airline->getSearchCode() : "") + "|" +
            QString::number(this->num_of_rows) + "|" +
            QString::number(this->num_of_cols) + "|" ;

    for (int i = 0; i < this->list_of_flights.size() && this->list_of_flights[i]; i++)
    {
        if (i == this->list_of_flights.size() - 1)
            str += this->list_of_flights[i]->getSearchCode();
        else
            str += this->list_of_flights[i]->getSearchCode() + "/";
    }

    str += "\n";

    return str;
}
int Airplane::getRowCount(){return this->num_of_rows;}
int Airplane::getcolumnCount(){return this->num_of_cols; }
Seat * Airplane::getSeat(int r,int c){
    return &seats[r][c];

}








