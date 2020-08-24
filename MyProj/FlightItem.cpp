#include "FlightItem.h"
#include "Flight.h"

extern bool ISDATACHANGED;

bool FlightItem::isFree(Flight * f) const
{
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

Flight* FlightItem::nextFlight(Flight * f) const{
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

Flight* FlightItem::prevFlight(Flight * f) const{
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

bool FlightItem::isFlightInList(Flight * f) const
{
    foreach (Flight* fl, this->list_of_flights)
    {
        if (fl == f)
            return true;
    }
    return false;
}

bool FlightItem::isDoneFlightInList(Flight * f) const
{
    foreach (Flight * ff, this->list_of_done_flights)
    {
        if (f == ff)
        {
            return true;
        }
    }
    return false;
}

Airline *FlightItem::getAirline() const
{
    return airline;
}

QVector<Flight *> FlightItem::getFlightList() const
{
    return list_of_flights;
}

QVector<Flight *> FlightItem::getDoneFlightList() const
{
    return list_of_done_flights;
}

void FlightItem::setAirline(Airline *value)
{
    if (value && !this->airline)
    {
        airline = value;

        ISDATACHANGED = true;
    }
}

void FlightItem::attachFlight(Flight * f)
{
    if (f && !this->isFlightInList(f))
    {
        this->list_of_flights.push_back(f);

        ISDATACHANGED = true;
    }
}

void FlightItem::attachDoneFlight(Flight * f)
{
    if (f && !this->isDoneFlightInList(f) && isFlightInList(f))
    {
        this->list_of_done_flights.push_back(f);
        ISDATACHANGED = true;
    }
}

void FlightItem::removeDoneFlight(Flight * f)
{
    if(f && isDoneFlightInList(f) && isFlightInList(f)){
        this->list_of_done_flights.removeOne(f);
        ISDATACHANGED = true;
    }
}

void FlightItem::removeFlight(Flight* f){
    if(f && isFlightInList(f)){
        this->list_of_flights.removeOne(f);

        ISDATACHANGED = true;
    }
}

int FlightItem::flightListSize() const{
    return list_of_flights.size();
}

int FlightItem::DoneFlightListSize() const{
    return list_of_done_flights.size();
}
