#include "Airline.h"

Airline::Airline()
{

}

Airline::Airline(const QString &name, const QString &code)
{
    this->setName(name);
    this->setCode(code);
}

QString Airline::get_data()
{
    QString str = this->name + "|" + this->code + "\n";
    return str;
}

void Airline::attachEmp(Employee * e)
{
    this->list_of_emps.push_back(e);
}

//void Airline::attachHost(Host * t)
//{
//    this->list_of_hosts.push_back(t);
//}

//void Airline::attachPilot(Pilot * t)
//{
//    this->list_of_pilots.push_back(t);
//}

void Airline::attachFlight(Flight * t)
{
    this->list_of_flights.push_back(t);
}

void Airline::attachAirplane(Airplane * t)
{
    this->list_of_airplanes.push_back(t);
}

void Airline::attachTicket(Ticket * t)
{
    this->list_of_tickets.push_back(t);
}

void Airline::setName(const QString &value)
{
    name = value;
}

void Airline::setCode(const QString &value)
{
    this->code = value;
    this->search_code = value;
}

QString Airline::getName() const
{
    return name;
}

QString Airline::getCode() const
{
    return code;
}
