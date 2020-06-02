#include "Airplane.h"
#include "Airline.h"
#include "Flight.h"
#include <QString>

void Airplane::attachFlight(Flight *f)
{
    if (f)
        this->list_of_flights.push_back(f);
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
    numOfSeats = value;
//    Recorder<Airplane>::getInstance()->updateFile(this);
}

QString Airplane::getSerial() const
{
    return serial;
}

void Airplane::setSerial(const QString &value)
{
    serial = value;
//    this->search_code = value;
    this->setSearchCode(value);
//    Recorder<Airplane>::getInstance()->updateFile(this);
}

bool Airplane::isFree(Flight * f)
{
    if (this->numOfSeats < f->getNumOfPassengers())
        return false;
    for (int i = 0; i < this->list_of_flights.size(); i++)
    {
        if ( !(
            (this->list_of_flights.at(i)->getDateTimeDeparture() > f->getDateTimeArrival() &&
             this->list_of_flights.at(i)->getSource() == f->getDestination()) ||
            (this->list_of_flights.at(i)->getDateTimeArrival() < f->getDateTimeDeparture() &&
             this->list_of_flights.at(i)->getDestination() == f->getSource())
              )
           )
        {
            return false;
        }
    }
    return true;
}

Airplane::Airplane(QString & str_data)
    : airline(nullptr)
{
    QStringList str_list = str_data.split('|');
    this->setSerial(str_list[0]);
    this->setAirline(Recorder<Airline>::getInstance()->searchByCode(str_list[1]));


    //QStringList product_date = str_list[2].split('/');
    //this->setProductDate(product_date[2].toInt(), product_date[0].toInt(), product_date[1].toInt());

    this->setNumOfSeats(str_list[2].toInt());

    QStringList flights = str_list[3].split('/');

    foreach (QString s, flights)
    {
        this->attachFlight(this->airline->searchFlightByCode(s));
    }
}

QString Airplane::get_data()
{
    QString str = this->search_code + "|" +
            (this->airline ? this->airline->getSearchCode() : "") + "|" +
            QString::number(this->numOfSeats) + "|";

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
