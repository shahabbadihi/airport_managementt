#include "Ticket.h"
#include "Flight.h"
#include "Passenger.h"
#include "Airline.h"
#include "GetPassengerFactory.h"
#include <QString>
#include <stdexcept>
#include <QDateTime>
using namespace std;

extern bool ISDATACHANGED;

long Ticket::getNo() const
{
    return this->no;
}

void Ticket::setNo(long value)
{
    if (value <= 0)
        throw invalid_argument("Ticket No Must Be Greater Than 0!");

    this->no = value;
    this->setSearchCode(QString::number(value));

    ISDATACHANGED = true;
}

Ticket::Ticket()
     : flight(nullptr), passenger(nullptr),
       price(0),
       seat(nullptr)
{

}

Ticket::Ticket(QString & str_data)
    : flight(nullptr), passenger(nullptr),
      price(0),
      seat(nullptr)
{
    QStringList str_list = str_data.split('|');

    this->setNo(str_list[0].toLong());

    this->setFlight(Recorder<Flight>::getInstance()->searchByCode(str_list[1]));
    this->setPassenger(Recorder<Passenger>::getInstance()->searchByCode(str_list[2]));

    if (str_list[3] != "-1" && this->getFlight()->getAirplane())
        this->setSeat(this->getFlight()->getAirplane()->getSeat(str_list[3].toInt(),str_list[4].toInt()));
    else
        this->setSeat(nullptr);

    this->setPrice(str_list[5].toDouble());
}

Ticket::Ticket(long no, const QDate &birth,
               const QDate& dep_date, qlonglong national_code,
               const QString &fname,
               const QString &lname,
               const QString &father_name)
    : flight(nullptr), passenger(nullptr),
      seat(nullptr)
{
    this->setNo(no);
    this->setPassenger(GetPassengerFactory::getInstance()->getPassenger(birth,
                                                                        dep_date,
                                                                        national_code,
                                                                        fname,
                                                                        lname,
                                                                        father_name));
    Recorder<Passenger>::getInstance()->record(this->passenger);
}

QString Ticket::get_data()
{
    QString str_data = QString::number(this->no) + "|" +
            (this->flight ? this->flight->getSerial() : "") + "|" +
            (this->passenger ? this->passenger->getSearchCode() : "") +"|" +
            (this->seat ? QString::number(seat->getRow()) : "-1") + "|" +
            (this->seat ? QString::number(seat->getColumn()) : "-1") +
            "|" + (this->price ? QString::number(this->price) : "")
            + "|\n"
            ;
    return str_data;
}

void Ticket::setSeat(Seat *s){
    seat=s;

    if (seat)
        seat->attachTicket(this);
}

void Ticket::setFlight(Flight * f)
{
    if (f->isPassengerExist(this->passenger))
    {
        return;
    }
    if (f && !this->flight)
    {
        this->flight = f;
        f->attachTicket(this);

        ISDATACHANGED = true;
    }
}


void Ticket::setPassenger(Passenger * p)
{
    if (p && !this->passenger)
    {
        this->passenger = p;
        p->attachTicket(this);

        ISDATACHANGED = true;
    }
}

Flight *Ticket::getFlight() const
{
    return this->flight;
}
QString Ticket::getPassengerName() const{
    return passenger->getFname()+" "+passenger->getLname();
}
Ticket::~Ticket(){

    if (flight)
        this->flight->removeTicket(this);
    if (passenger)
        this->passenger->removeTicket(this);

    if (this->passenger->isTicketListEmpty())
        Recorder<Passenger>::getInstance()->remove(this->passenger);

    if (seat)
        this->seat->removeTicket(this);

    ISDATACHANGED = true;
}
double Ticket::getPrice(){
    return price;
}
Passenger * Ticket::getPassenger(){

    return passenger;
}

void Ticket::setPrice(double p)
{
    this->price = this->passenger->getPrice(p);
}
