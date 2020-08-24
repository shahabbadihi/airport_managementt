#include "Carrier.h"
#include "Flight.h"
#include "Airline.h"
#include <QString>
#include <stdexcept>
using namespace std;

extern bool ISDATACHANGED;

QString Carrier::getSerial() const
{
    return serial;
}

void Carrier::setSerial(const QString &value)
{
    if (value == "")
        throw invalid_argument("Serial Is Empty");
    serial = value;
    this->setSearchCode(value);

    ISDATACHANGED = true;
}

bool Carrier::isFree(const QDateTime & t, const QString & s) const
{
    if (s != this->place)
        return false;
    else
    {
        foreach (Flight * f, this->list_of_flights)
        {
            if (this->getMission(f).contains(t.toString()))
            {
                return false;
            }
        }
    }
    return true;
}

bool Carrier::isFlightInList(Flight * f) const
{
    foreach (Flight* fl, this->list_of_flights)
    {
        if (fl == f)
            return true;
    }
    return false;
}

QString Carrier::getPlace() const
{
    return place;
}

QStringList Carrier::getMissionList() const
{
    QStringList missions;
    foreach (Flight* f, this->list_of_flights)
    {
        missions.push_back(getMission(f));
    }
    return missions;
}

QString Carrier::getMission(Flight *f) const
{
    if (isFlightInList(f))
    {
        if (f->getSource() == this->place)
            return f->getDateTimeDeparture().toString() + "DEP";
        else if (f->getDestination() == this->place)
            return f->getDateTimeArrival().toString() + "ARR";
    }
    return "";
}

void Carrier::setPlace(const QString &value)
{
    if (value == "")
        throw invalid_argument("Place Is Empty!");
    place = value;

    ISDATACHANGED = true;
}

Carrier::Carrier(QString & str_data)
{
    QStringList str_list = str_data.split('|');
    this->setSerial(str_list[0]);
    this->setPlace(str_list[1]);

    QStringList flights = str_list[2].split('/', Qt::SkipEmptyParts);

    foreach (QString s, flights)
    {
        this->attachFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }
}

Carrier::Carrier(const QString &serial, const QString &place)
{
    this->setSerial(serial);
    this->setPlace(place);
}

QString Carrier::get_data()
{
    QString str =
            this->serial + "|" +
            this->place + "|";
    foreach (Flight* f, this->list_of_flights)
    {
        if (f)
            str += f->getSearchCode() + "/";
    }

    str += "\n";

    return str;
}

void Carrier::attachFlight(Flight* f)
{
    if (f && !isFlightInList(f))
    {
        this->list_of_flights.push_back(f);

        ISDATACHANGED = true;
    }
}

void Carrier::removeFlight(Flight *f){
    this->list_of_flights.removeOne(f);

    ISDATACHANGED = true;
}
Carrier::~Carrier(){
     foreach(Flight* f,this->list_of_flights){
         if (f)
            f->removeCarrier(this);
     }

     ISDATACHANGED = true;
}





