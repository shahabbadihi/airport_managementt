#include "Airplane.h"
#include "Airline.h"
#include "Flight.h"
#include <QString>

void Airplane::attachFlight(Flight *f)
{
    this->list_of_flights.push_back(f);
}

Airline *Airplane::getAirline() const
{
    return this->airline;
}

void Airplane::setAirline(Airline *value)
{
    this->airline = value;
    if (value)
        value->attachAirplane(this);
}

int Airplane::getNumOfSeats() const
{
    return numOfSeats;
}

void Airplane::setNumOfSeats(int value)
{
    numOfSeats = value;
}

QString Airplane::getSerial() const
{
    return serial;
}

void Airplane::setSerial(const QString &value)
{
    serial = value;
    this->search_code = value;
}

Airplane::Airplane(QString & str_data)
{
    QStringList str_list = str_data.split('|');
    this->setAirline(Recorder<Airline>::getInstance()->searchByCode(str_list[0]));
    this->setSerial(str_list[1]);

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
    QString str = this->airline->getSearchCode() + "|" +
            this->search_code + "|" +

            this->numOfSeats + "|";

    for (int i = 0; i < this->list_of_flights.size(); i++)
    {
        if (i == this->list_of_flights.size() - 1)
            str += this->list_of_flights[i]->getSearchCode();
        else
            str += this->list_of_flights[i]->getSearchCode() + "/";
    }

    str += "\n";

    return str;
}
