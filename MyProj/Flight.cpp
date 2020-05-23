#include "Flight.h"
#include "Host.h"
void Flight::setSerial(long s)
{
    this->serial = s;
}

void Flight::setAirplaneSerial(long s)
{
    this->airplaneSerial = s;
}

void Flight::setSource(const QString & s)
{
    this->source = s;
}

void Flight::setDestination(const QString & s)
{
    this->destination = s;
}

void Flight::setDateTimeArrival(const QDateTime &d)
{
    this->dateTimeArrival.setDate(d.date());
    this->dateTimeArrival.setTime(d.time());
}

void Flight::setDateTimeArrival(const QDateTime && d)
{
    this->dateTimeArrival.setDate(d.date());
    this->dateTimeArrival.setTime(d.time());
}

void Flight::setDateTimeDeparture(const QDateTime & d)
{
    this->dateTimeDeparture.setDate(d.date());
    this->dateTimeDeparture.setTime(d.time());
}

void Flight::setDateTimeDeparture(const QDateTime && d)
{
    this->dateTimeDeparture.setDate(d.date());
    this->dateTimeDeparture.setTime(d.time());
}

void Flight::setPilot(Pilot * p)
{
    this->pilot = p;
    p->attachFlight(this);
}

void Flight::setNumOfHosts(int n)
{
    this->numOfHosts = n;
}

void Flight::setNumOfPassengers(int n)
{
    this->numOfPassengers = n;
}

void Flight::attachHost(Host * h)
{
    this->hosts.push_back(h);
    h->attachFlight(this);
}

void Flight::attachPassenger(Passenger * p)
{
    this->passengers.push_back(p);
}

QDateTime Flight::getDateTimeArrival()
{
    return this->dateTimeArrival;
}

QDateTime Flight::getDateTimeDeparture()
{
    return this->dateTimeDeparture;
}

QString Flight::getSource()
{
    return this->source;
}

QString Flight::getDestination()
{
    return this->destination;
}

int Flight::getNumOfHosts()
{
    return this->numOfHosts;
}

int Flight::getNumOfPassengers()
{
    return this->numOfPassengers;
}

Pilot *Flight::getPilot()
{
    return this->pilot;
}

QVector<Host *> Flight::getHostsList()
{
    return this->hosts;
}

//void Flight::setDate(const QDate & d)
//{
//    this->date.setDate(d.year(), d.month(), d.day());
//}

//void Flight::setDate(const QDate && d)
//{
//    this->date.setDate(d.year(), d.month(), d.day());
//}

//void Flight::setDate(int year, int month, int day)
//{
//    this->date.setDate(year, month, day);
//}

//void Flight::setTime(const QTime & t)
//{
//    this->time.setHMS(t.hour(), t.minute(), t.second());
//}

//void Flight::setTime(const QTime && t)
//{
//    this->time.setHMS(t.hour(), t.minute(), t.second());
//}

//void Flight::setTime(int hour, int minute, int second)
//{
//    this->time.setHMS(hour, minute, second);
//}

