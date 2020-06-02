#include "Airline.h"
#include "Airplane.h"
#include "Pilot.h"
#include "Host.h"
#include "Flight.h"
//#include "Ticket.h"
#include "Recorder.h"

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


    QStringList pilots = str_list[2].split('/');
    foreach (QString s, pilots)
    {
        this->attachPilot(Recorder<Pilot>::getInstance()->searchByCode(s));
    }

    QStringList hosts = str_list[3].split('/');
    foreach (QString s, hosts)
    {
        this->attachHost(Recorder<Host>::getInstance()->searchByCode(s));
    }

    QStringList flights = str_list[4].split('/');
    foreach (QString s, flights)
    {
        this->attachFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }

//    QStringList tickets = str_list[5].split('/');
//    foreach (QString s, tickets)
//    {
//        this->attachTicket(Recorder<Ticket>::searchByCode(s));
//    }
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
//    str += "|";
//    for (int i = 0; i < this->list_of_tickets.size(); i++)
//    {
//        if (i == this->list_of_tickets.size() - 1)
//            str += this->list_of_tickets[i]->getSearchCode();
//        else
//            str += this->list_of_tickets[i]->getSearchCode() + "/";
//    }
    str += "\n";
    return str;
}

//void Airline::attachEmp(Employee * e)
//{
//    this->list_of_emps.push_back(e);
//}

void Airline::attachHost(Host * t)
{
    this->list_of_hosts.push_back(t);
//    Recorder<Airline>::getInstance()->updateFile(this);
}

void Airline::attachPilot(Pilot * t)
{
    this->list_of_pilots.push_back(t);
//    Recorder<Airline>::getInstance()->updateFile(this);
}

void Airline::attachFlight(Flight * t)
{
    this->list_of_flights.push_back(t);
//    Recorder<Airline>::getInstance()->updateFile(this);
}

void Airline::attachAirplane(Airplane * t)
{
    this->list_of_airplanes.push_back(t);
//    Recorder<Airline>::getInstance()->updateFile(this);
}

//void Airline::attachTicket(Ticket * t)
//{
//    this->list_of_tickets.push_back(t);
//}

//void Airline::attachCarrier(Carrier * d)
//{
//    this->list_of_carriers.push_back(d);
//}

void Airline::setName(const QString &value)
{
    name = value;
//    Recorder<Airline>::getInstance()->updateFile(this);
}

void Airline::setCode(const QString &value)
{
    this->code = value;
    this->setSearchCode(value);
//    Recorder<Airline>::getInstance()->updateFile(this);
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
    for (int i = 0; i < this->list_of_hosts.size(); i++)
    {
        Airplane* a = this->list_of_airplanes[i];
        if (a->isFree(f))
            return a;
    }
    return nullptr;
}

//Employee *Airline::getFirstFreeEmp(Flight * f) const
//{
//    for (int i = 0; i < this->list_of_emps.size(); i++)
//    {
//        Employee* a = this->list_of_emps[i];
//        if (a->isFree(f))
//            return a;
//    }
//    return nullptr;
//}

Flight *Airline::searchFlightByCode(QString & code)
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
