#include "Flight.h"
#include "Host.h"
#include "addticket.h"
#include "Ticket.h"
#include "Airline.h"
#include "Airplane.h"
#include "Carrier.h"
#include <QString>
#include <QStringList>
#include <stdexcept>
#include <QMessageBox>
#include <QDateTime>
#include "Recorder.h"
using namespace std;

extern bool ISDATACHANGED;

Airline *Flight::getAirline() const
{
    return airline;

}

void Flight::setAirline(Airline *value)
{
    if (value && !this->airline)
    {
        airline = value;

        value->attachFlight(this);

        ISDATACHANGED = true;
    }
}

void Flight::setAirplane(Airplane *value)
{
    if (value && !this->airplane)
    {
        airplane = value;

        value->attachFlight(this);

        QString s1 = "Airplane ";
        QString s2 = " Setted For Flight ";
        emit flightStatusMsgSignal(s1 + this->airplane->getSerial() + s2 +
                                   this->getSerial());

        ISDATACHANGED = true;
    }
}

Carrier *Flight::getDeparture_carrier() const
{
    return departure_carrier;
}

void Flight::setDeparture_carrier(Carrier *value)
{

    if (value && !this->departure_carrier)
    {
        departure_carrier = value;
        value->attachFlight(this);

        QString s1 = "Departure Carrier ";
        QString s2 = " Setted For Flight ";
        emit flightStatusMsgSignal(s1 + this->departure_carrier->getSerial() + s2 +
                                   this->getSerial());

        ISDATACHANGED = true;
    }
}

Carrier *Flight::getArrival_carrier() const
{
    return arrival_carrier;
}

void Flight::setArrival_carrier(Carrier *value)
{
    if (value && !this->arrival_carrier)
    {
        arrival_carrier = value;
        value->attachFlight(this);

        QString s1 = "Arrival Carrier ";
        QString s2 = "Setted For Flight ";
        emit flightStatusMsgSignal(s1 + this->arrival_carrier->getSerial() + s2 +
                                   this->getSerial());

        ISDATACHANGED = true;
    }
}

Airplane *Flight::getAirplane() const
{
    return airplane;
}

bool Flight::isHostInList(Host* h) const
{
    foreach (Host* ho, this->hosts)
    {
        if (ho == h)
            return true;
    }
    return false;
}

bool Flight::isTicketInList(Ticket * t) const
{
    foreach (Ticket* ti, this->tickets)
    {
        if (ti == t)
            return true;
    }
    return false;
}

bool Flight::isPilotSetted() const
{
    return this->pilot ? true : false;
}

bool Flight::isHostEnough() const
{
    return this->numOfHosts == this->hosts.size() ? true : false;
}

bool Flight::isPassengerEnough() const
{
    return this->numOfPassengers >= this->capacity * 0.7 ? true : false;
}

bool Flight::isAirplaneSetted() const
{
    return this->airplane ? true : false;
}

bool Flight::isDepartureCarrierSetted() const
{
    return this->departure_carrier ? true : false;
}

bool Flight::isArrivalCarrierSetted() const
{
    return this->arrival_carrier ? true : false;
}

void Flight::delay(qint64 milliseconds)
{
    if (milliseconds > 3600000)
    {
        QMessageBox msg;
        msg.setText("This Amount Of Delay Is Prohibited In The Rules About Postponing!!\nPlease Decrease It If You Want To Delay This Flight");
        msg.exec();
        return;
    }
    Flight* temp = nullptr;
    if (this->pilot)
    {
        temp = this->pilot->nextFlight(this);
    }

    QVector<Flight*> nexts_in_host_list;
    for (int i = 0; i < this->hosts.size(); i++)
    {
        
        Flight* temp = this->hosts[i]->nextFlight(this);
        nexts_in_host_list.push_back(temp);
    }

    Flight* temp2 = nullptr;
    if (this->airplane)
    {
         temp2 = this->airplane->nextFlight(this);
        
    }
    
    this->setDateTimeDeparture(this->dateTimeDeparture.addMSecs(milliseconds));
    this->setDateTimeArrival(this->dateTimeArrival.addMSecs(milliseconds));

    this->setFlightState(DELAYED);

    if (temp)
    {
        if (haveInterference(this, temp))
        {
            temp->delay(milliseconds);
        }
    }
    
    foreach (Flight* f, nexts_in_host_list)
    {
        if (f)
        {
            if (haveInterference(this, f))
            {
                f->delay(milliseconds);
            }
        }
    }

    if (temp2)
    {
        if (haveInterference(this, temp2))
        {
            temp2->delay(milliseconds);
        }
    }
}

bool Flight::haveInterference(Flight *f1, Flight *f2)
{
    if ((f1->getDateTimeArrival() > f2->getDateTimeDeparture() &&
            f1->getDateTimeDeparture() < f2->getDateTimeArrival()) ||
            (f2->getDateTimeArrival() > f1->getDateTimeDeparture() &&
                        f2->getDateTimeDeparture() < f1->getDateTimeArrival()))
    {
        return true;
    }
    return false;
}

int Flight::getCapacity() const
{
    return capacity;
}

void Flight::setCapacity(int value)
{
    if (value <= 0)
        throw invalid_argument("Capacity Must Be Greater Than 0!");

    capacity = value;

    ISDATACHANGED = true;
}

state Flight::getFlightState() const
{
    return flightState;
}

QString Flight::getFlightStateAsString() const
{
    switch (this->flightState)
    {
    case READY:
        return "READY";
        break;
    case SUSPENDED:
        return "SUSPENDED";
        break;
    case ONAIR:
        return "ONAIR";
        break;
    case CANCELED:
        return "CANCELED";
        break;
    case DELAYED:
        return "DELAYED";
        break;
    case DONE:
        return "DONE";
        break;
    }
    return "";
}

void Flight::setFlightState(const state &value)
{
    if (value == DONE)
        emit flightDoneSignal(true);
    if (value == CANCELED)
        emit flightCanceledSignal(true);
    flightState = value;

//    Recorder<Flight>::getInstance()->updateFileAll();
    ISDATACHANGED = true;
}

void Flight::setFlightStateAsString(const QString &value)
{
    if (value == "CANCELED")
        this->setFlightState(CANCELED);
    else if (value == "ONAIR")
        this->setFlightState(ONAIR);
    else if (value == "DONE")
        this->setFlightState(DONE);
    else if (value == "SUSPENDED")
        this->setFlightState(SUSPENDED);
    else if (value == "DELAYED")
        this->setFlightState(DELAYED);
    else if (value == "READY")
        this->setFlightState(READY);
}

void Flight::setState()
{
    if (this->flightState == CANCELED)
        return;
    if (this->flightState == DONE)
        return;
    if ((this->flightState == SUSPENDED
            && QDateTime::currentDateTime().secsTo(this->dateTimeDeparture)
            < 15 * 60) || (this->flightState == SUSPENDED && QDateTime::currentDateTime()
                           > this->dateTimeArrival))
    {
        if (pilot)
            this->pilot->removeFlight(this);

        foreach (Ticket * t, this->tickets)
        {
            Recorder<Ticket>::getInstance()->remove(t);
        }

        if (airplane)
            this->airplane->removeFlight(this);
        foreach (Host * h, this->hosts)
        {
            h->removeFlight(this);
        }
        if (arrival_carrier)
            this->arrival_carrier->removeFlight(this);
        if (departure_carrier)
            this->departure_carrier->removeFlight(this);

        this->setFlightState(CANCELED);
        emit flightStatusChanged();
        return;
    }

    if (this->dateTimeDeparture <= QDateTime::currentDateTime() &&
            QDateTime::currentDateTime() < this->dateTimeArrival)
    {
        if (this->flightState != CANCELED && this->flightState != SUSPENDED)
        {
            this->setFlightState(ONAIR);
        }
    }

    else if (this->dateTimeArrival <= QDateTime::currentDateTime())
    {
        if (this->flightState != CANCELED && this->flightState != SUSPENDED)
        {
            this->pilot->attachDoneFlight(this);
            this->airplane->attachDoneFlight(this);
            foreach (Host* h, this->hosts)
            {
                h->attachDoneFlight(this);
            }

            this->setFlightState(DONE);
        }
    }

    else if (this->isPilotSetted() && this->isHostEnough() && this->isAirplaneSetted() &&
            this->isArrivalCarrierSetted() && this->isDepartureCarrierSetted() &&
            this->isPassengerEnough() && this->isCheckInCompleted())
    {
        this->setFlightState(READY);
    }

    if (!this->isPilotSetted())
    {
        this->setFlightState(SUSPENDED);
        this->setPilot(this->airline->getFirstFreePilot(this));
    }

    if (!this->isHostEnough())
    {
        this->setFlightState(SUSPENDED);
        this->attachHost(this->airline->getFirstFreeHost(this));
        if (this->isHostEnough())
        {
            QString s3 = "Flight ";
            QString s4 = " Now Has Enough Hosts!";
            QString ss = s3 + this->getSerial() + s4;
            emit flightStatusMsgSignal(ss);
        }
    }

    if (!this->isAirplaneSetted())
    {
        this->setFlightState(SUSPENDED);
        this->setAirplane(this->airline->getFirstFreeAirplane(this));
    }

    if (!this->isArrivalCarrierSetted())
    {
        this->setFlightState(SUSPENDED);
        this->setArrival_carrier(Recorder<Carrier>::getInstance()->getFirstFree(this->getDateTimeArrival(),
                                                                             this->getDestination()));
    }

    if (!this->isDepartureCarrierSetted())
    {
        this->setFlightState(SUSPENDED);
        this->setDeparture_carrier(Recorder<Carrier>::getInstance()->getFirstFree(this->getDateTimeDeparture(),
                                                                             this->getSource()));
    }

    if (!this->isPassengerEnough())
    {
        this->setFlightState(SUSPENDED);
    }

    if (!this->isCheckInCompleted())
    {
        this->setFlightState(SUSPENDED);
    }

    emit flightStatusChanged();

}

Flight::Flight()
    : flightState(SUSPENDED), numOfPassengers(0), pilot(nullptr),
      airline(nullptr), airplane(nullptr), departure_carrier(nullptr)
    , arrival_carrier(nullptr)
{

}

Flight::Flight(QString & data_str)
    : flightState(SUSPENDED), numOfPassengers(0), pilot(nullptr),
      airline(nullptr), airplane(nullptr), departure_carrier(nullptr),
      arrival_carrier(nullptr)
{
    QStringList str_list = data_str.split('|');
    str_list.replaceInStrings("\n", "");

    this->setSerial(str_list.at(0));
    this->setAirline(Recorder<Airline>::getInstance()->searchByCode(str_list[1]));
    this->setSource(str_list.at(2));
    this->setDestination(str_list.at(3));

    QStringList date_departure = str_list.at(4).split('/', Qt::SkipEmptyParts);
    QStringList time_departure = str_list.at(5).split(':');
    QStringList date_arrival = str_list.at(6).split('/', Qt::SkipEmptyParts);
    QStringList time_arrival = str_list.at(7).split(':');

    this->setDateTimeDeparture(date_departure.at(2).toInt(),
                               date_departure.at(0).toInt(),
                               date_departure.at(1).toInt(),
                               time_departure.at(0).toInt(),
                               time_departure.at(1).toInt(),
                               time_departure.at(2).toInt());

    this->setDateTimeArrival(date_arrival.at(2).toInt(),
                               date_arrival.at(0).toInt(),
                               date_arrival.at(1).toInt(),
                               time_arrival.at(0).toInt(),
                               time_arrival.at(1).toInt(),
                               time_arrival.at(2).toInt());

    this->setAirplane(Recorder<Airplane>::getInstance()->searchByCode(str_list[8]));
    this->setDeparture_carrier(Recorder<Carrier>::getInstance()->searchByCode(str_list[9]));
    this->setArrival_carrier(Recorder<Carrier>::getInstance()->searchByCode(str_list[10]));
    this->setPilot(Recorder<Pilot>::getInstance()->searchByCode(str_list.at(11)));

    this->setNumOfHosts(str_list.at(12).toInt());

    QStringList hosts = str_list[13].split('/', Qt::SkipEmptyParts);
    foreach (QString s, hosts)
    {
        this->attachHost(Recorder<Host>::getInstance()->searchByCode(s));
    }

    this->setCapacity(str_list[14].toInt());

    QStringList tickets = str_list[15].split('/', Qt::SkipEmptyParts);
    foreach (QString s, tickets)
    {
        this->attachTicket(Recorder<Ticket>::getInstance()->searchByCode(s));
    }

    this->setFlightStateAsString(str_list[16]);
}

Flight::Flight(const QString &serial, Airline *a,
               const QString &source, const QString &dest,
               const QDateTime &dp_datetime, const QDateTime &ar_datetime,
               int num_hosts, int capacity)
    : flightState(SUSPENDED), numOfPassengers(0), pilot(nullptr),
      airline(nullptr), airplane(nullptr), departure_carrier(nullptr),
      arrival_carrier(nullptr)
{
    this->setSerial(serial);
    this->setAirline(a);
    this->setSource(source);
    this->setDestination(dest);
    this->setDateTimeDeparture(dp_datetime);
    this->setDateTimeArrival(ar_datetime);
    this->setNumOfHosts(num_hosts);
    this->setCapacity(capacity);
}

QString Flight::get_data()
{
    QString data_str = this->serial + "|";

    data_str += (this->airline ? this->airline->getSearchCode() : "") + "|";
    data_str += this->source + "|" +
            this->destination + "|";

    data_str += QString::number(this->dateTimeDeparture.date().month()) + "/" +
                 QString::number(this->dateTimeDeparture.date().day()) + "/" +
                  QString::number(this->dateTimeDeparture.date().year()) + "|" +

             QString::number(this->dateTimeDeparture.time().hour()) + ":" +
             QString::number(this->dateTimeDeparture.time().minute()) + ":" +
             QString::number(this->dateTimeDeparture.time().second()) + "|" +

             QString::number(this->dateTimeArrival.date().month()) + "/" +
             QString::number(this->dateTimeArrival.date().day()) + "/" +
             QString::number(this->dateTimeArrival.date().year()) + "|" +

             QString::number(this->dateTimeArrival.time().hour()) + ":" +
             QString::number(this->dateTimeArrival.time().minute()) + ":" +
             QString::number(this->dateTimeArrival.time().second()) + "|";

    data_str += (this->airplane ? this->airplane->getSearchCode() : "") + "|" +
            (this->departure_carrier ? this->departure_carrier->getSearchCode() : "") + "|" +
            (this->arrival_carrier ? this->arrival_carrier->getSearchCode() : "") + "|";

    data_str += (this->pilot ? QString::number(this->pilot->getPersonnelCode()) : "") + "|";
    data_str += QString::number(this->numOfHosts) + "|";

    foreach (Host* h, this->hosts)
    {
        if (h)
            data_str += h->getSearchCode() + "/";
    }

    data_str += "|" + QString::number(this->capacity) + "|";

    foreach (Ticket* t, this->tickets)
    {
        if (t)
            data_str += t->getSearchCode() + "/";
    }
    data_str += "|" + this->getFlightStateAsString() + "\n";

    return data_str;

}

QString Flight::getFlightStr() const
{
    return this->airline->getName() + " " + this->serial + " " +
            this->source + " " + this->destination + " " +
            this->dateTimeDeparture.toString() + " " + this->dateTimeArrival.toString() + " " +
            this->getFlightStateAsString();
}

void Flight::setSerial(const QString& s)
{
    if (s == "")
        throw invalid_argument("Serial Is Empty!");

    this->serial = s;
    this->setSearchCode(s);

    ISDATACHANGED = true;
}

void Flight::setSource(const QString & s)
{
    if (s == "")
        throw invalid_argument("Source Is Empty!");

    this->source = s;

    ISDATACHANGED = true;
}

void Flight::setDestination(const QString & s)
{
    if (s == "")
        throw invalid_argument("Destination Is Empty!");

    this->destination = s;

    ISDATACHANGED = true;
}

void Flight::setDateTimeArrival(const QDateTime &d)
{
    if (d <= this->dateTimeDeparture)
        throw invalid_argument("Arrival DateTime Must Be After The Departure DateTime!");

//    qint64 duration = this->dateTimeDeparture.secsTo(d);
//    if (duration < 4500)
//        throw invalid_argument("The Duration Of The Flight Must Be At Least 1 Hour and 15 Minutes!!");

    this->dateTimeArrival.setDate(d.date());
    this->dateTimeArrival.setTime(d.time());

    ISDATACHANGED = true;
}

void Flight::setDateTimeArrival(const QDateTime && d)
{
    if (d <= this->dateTimeDeparture)
        throw invalid_argument("Arrival DateTime Must Be After The Departure DateTime!");

//    qint64 duration = this->dateTimeDeparture.secsTo(d);
//    if (duration < 4500)
//        throw invalid_argument("The Duration Of The Flight Must Be At Least 1 Hour and 15 Minutes!!");

    this->dateTimeArrival.setDate(d.date());
    this->dateTimeArrival.setTime(d.time());

    ISDATACHANGED = true;
}

void Flight::setDateTimeArrival(int year, int month, int day, int hour, int minute, int second)
{
    QDate date(year, month, day);
    QTime time(hour, minute, second);
    QDateTime datetime(date, time);
    this->setDateTimeArrival(datetime);
}

void Flight::setDateTimeDeparture(const QDateTime & d)
{
    this->dateTimeDeparture.setDate(d.date());
    this->dateTimeDeparture.setTime(d.time());

    ISDATACHANGED = true;
}

void Flight::setDateTimeDeparture(const QDateTime && d)
{
    this->dateTimeDeparture.setDate(d.date());
    this->dateTimeDeparture.setTime(d.time());

    ISDATACHANGED = true;
}

void Flight::setDateTimeDeparture(int year, int month, int day, int hour, int minute, int second)
{
    QDate date(year, month, day);
    QTime time(hour, minute, second);
    QDateTime datetime(date, time);
    this->setDateTimeDeparture(datetime);
}

void Flight::setPilot(Pilot * p)
{
    if (p && !this->pilot)
    {
        this->pilot = p;

        p->attachFlight(this);

        QString s1 = "Pilot ";
        QString s2 = " Setted For Flight ";
        emit flightStatusMsgSignal(s1 + QString::number(this->getPilot()->getPersonnelCode()) + s2 +
                                   this->getSerial());

        ISDATACHANGED = true;
    }
}

void Flight::setNumOfHosts(int n)
{
    if (n <= 0)
        throw invalid_argument("Num Of Hosts Must Be Greater Than 0!");

    this->numOfHosts = n;

    ISDATACHANGED = true;
}

void Flight::setNumOfPassengers(int n)
{
    if (n <= 0)
        throw invalid_argument("Num Of Passengers Must Be Greater Than 0!");

    this->numOfPassengers = n;

    ISDATACHANGED = true;
}

void Flight::attachHost(Host * h)
{
    if (h && !this->isHostInList(h))
    {
        this->hosts.push_back(h);

        h->attachFlight(this);

        QString s1 = "Host ";
        QString s2 = " Setted For Flight ";
        emit flightStatusMsgSignal(s1 + QString::number(h->getPersonnelCode()) + s2 +
                                   this->getSerial());

        ISDATACHANGED = true;

    }
}


void Flight::attachTicket(Ticket * p)
{
    if (p && !this->isTicketInList(p))
    {
        this->tickets.push_back(p);
        this->numOfPassengers++;
        p->setFlight(this);

        QString s1 = "Ticket ";
        QString s2 = " Setted For Flight ";
        emit flightStatusMsgSignal(s1 + QString::number(p->getNo()) + s2 +
                                   this->getSerial());

        ISDATACHANGED = true;

    }
}

void Flight::removeHost(Host* h)
{
    this->hosts.removeOne(h);

    ISDATACHANGED = true;
}
void Flight::removePilot(){

    this->pilot = nullptr;

    ISDATACHANGED = true;    
}

void Flight::removeAirplane()
{
    this->airplane = nullptr;

    ISDATACHANGED = true;
}

QDateTime Flight::getDateTimeArrival() const
{
    return this->dateTimeArrival;
}

QDateTime Flight::getDateTimeDeparture() const
{
    return this->dateTimeDeparture;
}

QString Flight::getSource() const
{
    return this->source;
}

QString Flight::getDestination() const
{
    return this->destination;
}

int Flight::getNumOfHosts() const
{
    return this->numOfHosts;
}

int Flight::getNumOfPassengers() const
{
    return this->numOfPassengers;
}

Pilot *Flight::getPilot() const
{
    return this->pilot;
}

QVector<Host *> Flight::getHostsList() const
{
    return this->hosts;
}

QString Flight::getSerial() const
{
    return this->serial;
}

Flight::~Flight()
{
    foreach (Host* h, this->getHostsList())
    {
        h->removeFlight(this);
    }
    if (this->pilot)
        this->pilot->removeFlight(this);
    if (this->airline)
        this->airline->removeFlight(this);
    if (this->airplane)
        this->airplane->removeFlight(this);
    if (this->departure_carrier)
        this->departure_carrier->removeFlight(this);
    if (this->arrival_carrier)
        this->arrival_carrier->removeFlight(this);
    foreach (Ticket* t, this->tickets)
    {
        Recorder<Ticket>::getInstance()->remove(t);
    }

    emit flightStatusChanged();
    ISDATACHANGED = true;

}

void Flight::removeCarrier(Carrier* c){
    if(c==arrival_carrier){
        arrival_carrier=Recorder<Carrier>::getInstance()->getFirstFree(getDateTimeArrival(),getDestination());
        ISDATACHANGED = true;
    }
    else if(c==departure_carrier){
        departure_carrier=Recorder<Carrier>::getInstance()->getFirstFree(getDateTimeDeparture(),getSource());
        ISDATACHANGED = true;
    }
}
int Flight::getAttachedTicketsize()const{
    return tickets.size();
}
void Flight::removeTicket(Ticket* T){
   tickets.removeOne(T);
}
bool Flight::isCheckInReady()const{
    if(QDateTime::currentDateTime().secsTo(dateTimeDeparture)<=2*60*60 &&
            isAirplaneSetted()){
        return true;
    }
    else{
        return false;
    }
}

bool Flight::isSuitable(Passenger *p, const QString &source,
                        const QString &dest, const QDate &dep_date
                        ) const
{
    if (this->getSource() == source &&
                        this->getDestination() == dest &&
                        this->getDateTimeDeparture().date() == dep_date &&
                        this->getNumOfPassengers() < this->getCapacity() &&
                        !this->isPassengerExist(p) && (flightState == SUSPENDED
                                                       || flightState == READY ||
                                                       flightState == DELAYED)
            )
    {
        return true;
    }
    return false;
}

bool Flight::isPassengerExist(Passenger * p) const
{
    if (p)
    {
        foreach (Ticket * t, this->tickets)
        {
            if (p == t->getPassenger())
            {
                return true;
            }
        }
    }
    return false;
}

double Flight::income() const
{
    double in = 0;
    foreach(Ticket * t, this->tickets)
    {
        in += t->getPrice();
    }
    return in;
}

bool Flight::isCheckInCompleted(){
    if (this->airplane)
    {
        int freeSeats=0;
        for(int i=0;i<airplane->getRowCount();i++){
            for(int j=0;j<airplane->getcolumnCount();j++){
               if( this->airplane->getSeat(i,j)->isFree(this)){
                   freeSeats++;
               }
            }
        }
        if(freeSeats==airplane->getNumOfSeats()-tickets.size()){return true;}
        else{return false;}
    }
    return true;
}
