#include "Flight.h"
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

