#include "Ticket.h"
#include "Flight.h"
#include "Passenger.h"
#include "Airline.h"
#include <QString>
#include <stdexcept>
using namespace std;

long Ticket::getNo() const
{
    return this->no;
}

//void Ticket::setAirline(Airline *value)
//{
//    airline = value;
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

void Ticket::setNo(long value)
{
    if (value <= 0)
        throw invalid_argument("Ticket No Must Be Greater Than 0!");

    this->no = value;
//    this->search_code = QString::number(value);
    this->setSearchCode(QString::number(value));
//    Recorder<Ticket>::getInstance()->updateFile(this);
}

Ticket::Ticket()
     : flight(nullptr), passenger(nullptr),
       seat(nullptr)
{

}

Ticket::Ticket(QString & str_data)
    : flight(nullptr), passenger(nullptr),
      seat(nullptr)
{
    QStringList str_list = str_data.split('|');

    this->setNo(str_list[0].toLong());
    //this->setAirline(Recorder<Airline>::getInstance()->searchByCode(str_list[1]));

    this->setFlight(Recorder<Flight>::getInstance()->searchByCode(str_list[1]));
    this->setPassenger(Recorder<Passenger>::getInstance()->searchByCode(str_list[2]));

    if (str_list[3] != "-1")
        this->setSeat(this->getFlight()->getAirplane()->getSeat(str_list[3].toInt(),str_list[4].toInt()));
    else
        this->setSeat(nullptr);
}

Ticket::Ticket(long no, const QDate &birth,
               const QDate& dep_date, qlonglong national_code,
               const QString &fname,
               const QString &lname,
               const QString &father_name, Flight * f)
    : flight(nullptr), passenger(nullptr),
      seat(nullptr)
{
    this->setNo(no);
    this->setPassenger(new Passenger(fname, birth, dep_date, national_code, lname,
                                     father_name));
    Recorder<Passenger>::getInstance()->add(this->passenger);
    this->setFlight(f);
}

QString Ticket::get_data()
{
    QString str_data = QString::number(this->no) + "|" +
            (this->flight ? this->flight->getSerial() : "") + "|" +
            (this->passenger ? this->passenger->getSearchCode() : "") +"|" +
            (this->seat ? QString::number(seat->getRow()) : "-1") + "|" +
            (this->seat ? QString::number(seat->getColumn()) : "-1") +
            "|\n"
            ;
    return str_data;
}

void Ticket::setSeat(Seat *s){
    seat=s;

    if (seat)
        seat->attachTicket(this);
}
//void Ticket::setDestination(const QString & d)
//{
//    this->destination = d;
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setSource(const QString & s)
//{
//    this->source = s;
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setPassengerFname(const QString & fname)
//{
//    this->passengerFname = fname;
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setPassengerLname(const QString & lname)
//{
//    this->passengerLname = lname;
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setPassengerNationalCode(long n)
//{
//    this->passengerNationalCode = n;
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setDateFlight(const QDate & date)
//{
//    this->flightDate.setDate(date.year(), date.month(), date.day());
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setDateFlight(const QDate && date)
//{
//    this->flightDate.setDate(date.year(), date.month(), date.day());
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setTimeFlight(const QTime & time)
//{
//    this->flightTime.setHMS(time.hour(), time.minute(), time.second());
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setTimeFlight(const QTime && time)
//{
//    this->flightTime.setHMS(time.hour(), time.minute(), time.second());
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setDateTimeArrival(const QDateTime & d)
//{
//    this->flightDateTimeArrival.setDate(d.date());
//    this->flightDateTimeArrival.setTime(d.time());
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setDateTimeArrival(const QDateTime && d)
//{
//    this->flightDateTimeArrival.setDate(d.date());
//    this->flightDateTimeArrival.setTime(d.time());
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

void Ticket::setFlight(Flight * f)
{
    if (f && !this->flight)
    {
        this->flight = f;
        f->attachTicket(this);
    }
    //    Recorder<Ticket>::getInstance()->updateFile(this);
}


void Ticket::setPassenger(Passenger * p)
{
    if (p && !this->passenger)
    {
        this->passenger = p;
        p->attachTicket(this);
    }
//    this->setPassengerFname(p->getFname());
//    this->setPassengerLname(p->getLname());
//    this->setPassengerNationalCode(p->getNationalCode());
//    this->setPassengerFatherName(p->getFatherName());
//    this->setPassengerBirthDate(p->getBirthDate());

//    Recorder<Ticket>::getInstance()->updateFile(this);
}

//void Ticket::setPassengerBirthDate(const QDate & date)
//{
//    this->passengerBirthDate.setDate(date.year(), date.month(), date.day());
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setPassengerBirthDate(const QDate && date)
//{
//    this->passengerBirthDate.setDate(date.year(), date.month(), date.day());
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//void Ticket::setPassengerFatherName(const QString & father_name)
//{
//    this->passengerFatherName = father_name;
//    Recorder<Ticket>::getInstance()->updateFile(this);
//}

//QString Ticket::getSource()
//{
//    return this->source;
//}

//QString Ticket::getDestination()
//{
//    return this->destination;
//}

//QDate Ticket::getDateFlight()
//{
//    return this->flightDate;
//}

Flight *Ticket::getFlight() const
{
    return this->flight;
}
QString Ticket::getPassengerName(){
    return passenger->getFname()+" "+passenger->getLname();
}
Ticket::~Ticket(){
    this->flight->removeTicket(this);
    this->passenger->removeTicket(this);

    if (this->passenger->isTicketListEmpty())
        Recorder<Passenger>::getInstance()->remove(this->passenger);

    this->seat->removeTicket();
}
Price Ticket::getPrice(){
    return price;
}
Passenger * Ticket::getPassenger(){

    return passenger;
}
