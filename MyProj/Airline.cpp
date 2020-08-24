#include "Airline.h"
#include "Airplane.h"
#include "Pilot.h"
#include "Host.h"
#include "Flight.h"
#include "Recorder.h"
#include <stdexcept>
using namespace std;

extern bool ISDATACHANGED;

Airline::Airline(const QString &name, const QString &code)
{
    this->setCode(code);
    this->setName(name);
}

Airline::Airline(QString & str_data)
{
    QStringList str_list = str_data.split('|');

    this->setCode(str_list[0]);
    this->setName(str_list[1]);


    QStringList pilots = str_list[2].split('/', Qt::SkipEmptyParts);
    foreach (QString s, pilots)
    {
        this->attachPilot(Recorder<Pilot>::getInstance()->searchByCode(s));
    }

    QStringList hosts = str_list[3].split('/', Qt::SkipEmptyParts);
    foreach (QString s, hosts)
    {
        this->attachHost(Recorder<Host>::getInstance()->searchByCode(s));
    }

    QStringList flights = str_list[4].split('/', Qt::SkipEmptyParts);
    foreach (QString s, flights)
    {
        this->attachFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }

    return;
}

Airline::~Airline()
{
    foreach (Host * h, this->list_of_hosts)
    {
        Recorder<Host>::getInstance()->remove(h);
    }
    foreach (Pilot * p, this->list_of_pilots)
    {
        Recorder<Pilot>::getInstance()->remove(p);
    }
    foreach (Flight * f, this->list_of_flights)
    {
        Recorder<Flight>::getInstance()->remove(f);
    }
    foreach (Airplane * a, this->list_of_airplanes)
    {
        Recorder<Airplane>::getInstance()->remove(a);
    }

    ISDATACHANGED = true;
}

QString Airline::get_data()
{
    QString str = this->code + "|" + this->name + "|";
    for (int i = 0; i < this->list_of_pilots.size() && this->list_of_pilots[i]; i++)
    {
        if (i == this->list_of_pilots.size() - 1)
            str += this->list_of_pilots[i]->getSearchCode();
        else
            str += this->list_of_pilots[i]->getSearchCode() + "/";
    }
    str += "|";
    for (int i = 0; i < this->list_of_hosts.size() && this->list_of_hosts[i]; i++)
    {
        if (i == this->list_of_hosts.size() - 1)
            str += this->list_of_hosts[i]->getSearchCode();
        else
            str += this->list_of_hosts[i]->getSearchCode() + "/";
    }
    str += "|";
    for (int i = 0; i < this->list_of_flights.size() && this->list_of_flights[i]; i++)
    {
        if (i == this->list_of_flights.size() - 1)
            str += this->list_of_flights[i]->getSearchCode();
        else
            str += this->list_of_flights[i]->getSearchCode() + "/";
    }
    str += "|";

    str += "\n";
    return str;
}

void Airline::attachHost(Host * t)
{
    if (t)
    {
        this->list_of_hosts.push_back(t);
        ISDATACHANGED = true;
    }
}

void Airline::attachPilot(Pilot * t)
{
    if (t)
    {
        this->list_of_pilots.push_back(t);

        ISDATACHANGED = true;
    }
}

void Airline::attachFlight(Flight * t)
{
    if (t && !isFlightInList(t))
    {
        this->list_of_flights.push_back(t);
        t->setAirline(this);

        ISDATACHANGED = true;
    }
}

void Airline::attachAirplane(Airplane * t)
{
    if (t)
    {
        this->list_of_airplanes.push_back(t);

        ISDATACHANGED = true;
    }
}

void Airline::removeHost(Host * host)
{
    this->list_of_hosts.removeOne(host);

    ISDATACHANGED = true;
}

void Airline::removePilot(Pilot * pilot)
{
    this->list_of_pilots.removeOne(pilot);

    ISDATACHANGED = true;
}

void Airline::removeFlight(Flight *f)
{
    this->list_of_flights.removeOne(f);

    ISDATACHANGED = true;
}

void Airline::removeAirplane(Airplane * a)
{
    this->list_of_airplanes.removeOne(a);

    ISDATACHANGED = true;
}

bool Airline::isFlightInList(Flight * f) const
{
    foreach (Flight* fl, this->list_of_flights)
    {
        if (fl == f)
            return true;
    }
    return false;
}

void Airline::setName(const QString &value)
{
    if (value == "")
        throw invalid_argument("Name Is Empty!");
    name = value;

    ISDATACHANGED = true;
}

void Airline::setCode(const QString &value)
{
    if (value == "")
        throw invalid_argument("Code Is Empty!");
    this->code = value;
    this->setSearchCode(value);

    ISDATACHANGED = true;
}

QString Airline::getName() const
{
    return name;
}

QString Airline::getCode() const
{
    return code;
}

Pilot *Airline::getFirstFreePilot(Flight* f) const
{
    for (int i = 0; i < this->list_of_pilots.size(); i++)
    {
        Pilot* a = this->list_of_pilots[i];
        if (a->isFree(f))
            return a;
    }
    return nullptr;
}

Host *Airline::getFirstFreeHost(Flight* f) const
{
    for (int i = 0; i < this->list_of_hosts.size(); i++)
    {
        Host* a = this->list_of_hosts[i];
        if (a->isFree(f))
            return a;
    }
    return nullptr;
}

Airplane *Airline::getFirstFreeAirplane(Flight * f) const
{
    for (int i = 0; i < this->list_of_airplanes.size(); i++)
    {
        Airplane* a = this->list_of_airplanes[i];

        if (a->isFree(f))
            return a;
    }
    return nullptr;
}

Flight *Airline::searchFlightByCode(QString & code) const
{
    foreach (Flight* f, this->list_of_flights)
    {
        if (f && f->getSearchCode() == code)
        {
            return f;
        }
    }
    return nullptr;
}
QVector<Pilot*>Airline::getPilotsList() const{return list_of_pilots;}
QVector<Host*>Airline::getHostsList() const{return list_of_hosts;}
QVector<Flight*>Airline::getFlightsList() const{return list_of_flights;}
QVector<Airplane*>Airline::getAirplanesList() const{return list_of_airplanes;}



