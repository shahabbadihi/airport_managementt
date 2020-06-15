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

Airplane::Airplane(QString & str_data)
    : airline(nullptr)
{
    QStringList str_list = str_data.split('|');
    this->setSerial(str_list[0]);
    this->setAirline(Recorder<Airline>::getInstance()->searchByCode(str_list[1]));


    //QStringList product_date = str_list[2].split('/', Qt::SkipEmptyParts);
    //this->setProductDate(product_date[2].toInt(), product_date[0].toInt(), product_date[1].toInt());

    this->setNumOfSeats(str_list[2].toInt());

    QStringList flights = str_list[3].split('/', Qt::SkipEmptyParts);

    foreach (QString s, flights)
    {
        this->attachFlight(this->airline->searchFlightByCode(s));
    }
}

QString Airplane::get_data()
{
    QString str = this->getSearchCode() + "|" +
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
