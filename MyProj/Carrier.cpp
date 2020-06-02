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
//    this->search_code = value;
    this->setSearchCode(value);
//    Recorder<Carrier>::getInstance()->updateFile(this);
}

bool Carrier::isFree(const QDateTime & t, const QString & s)
{
    if (s != this->place)
        return false;
    else
    {
        foreach (QString str, this->list_of_missions)
        {
            if (str.contains(t.toString()))
            {
                return false;
            }
        }
    }
    return true;
}

bool Carrier::isFlightInList(Flight * f)
{
    foreach (Flight* fl, this->list_of_flights)
    {
        if (fl == f)
            return true;
    }
    return false;
}

bool Carrier::isMissionInList(const QString & str)
{
    foreach (QString s, this->list_of_missions)
    {
        if (str == s)
            return true;
    }
    return false;
}

//Airline *Carrier::getAirline() const
//{
//    return airline;
//}

//void Carrier::setAirline(Airline *value)
//{
//    airline = value;
//}

QString Carrier::getPlace() const
{
    return place;
}

void Carrier::setPlace(const QString &value)
{
    place = value;
//    Recorder<Carrier>::getInstance()->updateFile(this);
}

Carrier::Carrier(QString & str_data)
{
    QStringList str_list = str_data.split('|');
    //this->setAirline(Recorder<Airline>::getInstance()->searchByCode(str_list[0]));
    this->setSerial(str_list[0]);
    this->setPlace(str_list[1]);

    QStringList flights = str_list[2].split('/', Qt::SkipEmptyParts);

    foreach (QString s, flights)
    {
        this->attachFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }

    QStringList missions = str_list[3].split('/', Qt::SkipEmptyParts);

    foreach (QString s, missions)
    {
        this->attachMission(s);
    }
}

QString Carrier::get_data()
{
    QString str = /*this->airline->getSearchCode() + "|" +*/
            this->serial + "|" +
            this->place + "|";
    foreach (Flight* f, this->list_of_flights)
    {
        if (f)
            str += f->getSearchCode() + "/";
    }

    str += "|";

    foreach (QString s, this->list_of_missions)
    {
        str += s + "/";
    }

    str += "\n";

    return str;
}

void Carrier::attachFlight(Flight* f)
{
    if (f)
    {
        this->list_of_flights.push_back(f);
    }
//    Recorder<Carrier>::getInstance()->updateFile(this);
}

void Carrier::attachMission(const QString & m)
{
    if (!this->isMissionInList(m))
        this->list_of_missions.push_back(m);
//    Recorder<Carrier>::getInstance()->updateFile(this);
}
