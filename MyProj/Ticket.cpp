#include "Ticket.h"
#include "Flight.h"
#include "Passenger.h"
#include "Airline.h"
#include <QString>

long Ticket::getNo() const
{
    return this->no;
}

void Ticket::setAirline(Airline *value)
{
    airline = value;
}

void Ticket::setNo(long value)
{
    this->no = value;
    this->search_code = QString::number(value);
}

Ticket::Ticket(QString & str_data)
{
    QStringList str_list = str_data.split('|');

    this->setAirline(Recorder<Airline>::getInstance()->searchByCode(str_list[0]));
    this->setNo(str_list[1].toLong());
    this->setFlight(this->airline->searchFlightByCode(str_list[2]));
    this->setPassenger(Recorder<Passenger>::getInstance()->searchByCode(str_list[3]));
}

QString Ticket::get_data()
{
    QString str_data = this->airline->getCode() + "|" + QString::number(this->no) + "|" +
            QString::number(this->flightSerialCode) + "|" +
            QString::number(this->passengerNationalCode) + "|\n"
            ;
    return str_data;
}

void Ticket::setDestination(const QString & d)
{
    this->destination = d;
}

void Ticket::setSource(const QString & s)
{
    this->source = s;
}

void Ticket::setPassengerFname(const QString & fname)
{
    this->passengerFname = fname;
}

void Ticket::setPassengerLname(const QString & lname)
{
    this->passengerLname = lname;
}

void Ticket::setPassengerNationalCode(long n)
{
    this->passengerNationalCode = n;
}

void Ticket::setDateFlight(const QDate & date)
{
    this->flightDate.setDate(date.year(), date.month(), date.day());
}

void Ticket::setDateFlight(const QDate && date)
{
    this->flightDate.setDate(date.year(), date.month(), date.day());
}

void Ticket::setTimeFlight(const QTime & time)
{
    this->flightTime.setHMS(time.hour(), time.minute(), time.second());
}

void Ticket::setTimeFlight(const QTime && time)
{
    this->flightTime.setHMS(time.hour(), time.minute(), time.second());
}

void Ticket::setDateTimeArrival(const QDateTime & d)
{
    this->flightDateTimeArrival.setDate(d.date());
    this->flightDateTimeArrival.setTime(d.time());
}

void Ticket::setDateTimeArrival(const QDateTime && d)
{
    this->flightDateTimeArrival.setDate(d.date());
    this->flightDateTimeArrival.setTime(d.time());
}

void Ticket::setFlight(Flight * f)
{
    this->flight = f;
    if (f)
    {
        f->attachTicket(this);
    }
}

void Ticket::setPassenger(Passenger * p)
{
    this->passenger = p;
    this->setPassengerFname(p->getFname());
    this->setPassengerLname(p->getLname());
    this->setPassengerNationalCode(p->getNationalCode());
    this->setPassengerFatherName(p->getFatherName());
    this->setPassengerBirthDate(p->getBirthDate());
}

void Ticket::setPassengerBirthDate(const QDate & date)
{
    this->passengerBirthDate.setDate(date.year(), date.month(), date.day());
}

void Ticket::setPassengerBirthDate(const QDate && date)
{
    this->passengerBirthDate.setDate(date.year(), date.month(), date.day());
}

void Ticket::setPassengerFatherName(const QString & father_name)
{
    this->passengerFatherName = father_name;
}

QString Ticket::getSource()
{
    return this->source;
}

QString Ticket::getDestination()
{
    return this->destination;
}

QDate Ticket::getDateFlight()
{
    return this->flightDate;
}

Flight *Ticket::getFlight() const
{
    return this->flight;
}
