#include "Carrier.h"
#include "Flight.h"
#include "Airline.h"
#include <QString>

QString Carrier::getSerial() const
{
    return serial;
}

void Carrier::setSerial(const QString &value)
{
    serial = value;
    this->search_code = value;
}

Airline *Carrier::getAirline() const
{
    return airline;
}

void Carrier::setAirline(Airline *value)
{
    airline = value;
}

Carrier::Carrier(QString & str_data)
{
    QStringList str_list = str_data.split('|');
    this->setAirline(Recorder<Airline>::searchByCode(str_list[0]));
    this->setSerial(str_list[1]);

    QStringList flights = str_list[2].split('/');

    foreach (QString s, flights)
    {
        this->attachFlight(this->airline->searchFlightByCode(s));
    }
}

QString Carrier::get_data()
{
    QString str = this->airline->getSearchCode() + "|" +
            this->serial + "|";
    foreach (Flight* f, this->list_of_flights)
    {
        str += f->getSearchCode() + "/";
    }

    str += "\n";

    return str;
}

QString Carrier::attachFlight(Flight* f)
{
    this->list_of_flights.push_back(f);
}
