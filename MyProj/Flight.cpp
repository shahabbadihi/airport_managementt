#include "Flight.h"
#include "Host.h"
#include "Ticket.h"
#include "Airline.h"
#include "Airplane.h"
#include "Carrier.h"
#include "OutOfDateException.h"
#include <QString>
#include <QStringList>
#include <stdexcept>
using namespace std;

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
        emit flightStatusChanged();
    }
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setAirplane(Airplane *value)
{
    if (value && !this->airplane)
    {
        airplane = value;

        value->attachFlight(this);
        emit flightStatusChanged();
    }
//    Recorder<Flight>::getInstance()->updateFile(this);
}

//Carrier *Flight::getCarrier() const
//{
//    return carrier;
//}

//void Flight::setCarrier(Carrier *value)
//{
//    carrier = value;
//}

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
        value->attachMission(this->dateTimeDeparture.toString() + "DEP");
        emit flightStatusChanged();
    }
//    Recorder<Flight>::getInstance()->updateFile(this);
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
        value->attachMission(this->dateTimeArrival.toString() + "ARR");
        emit flightStatusChanged();
    }
//    Recorder<Flight>::getInstance()->updateFile(this);
}

Airplane *Flight::getAirplane() const
{
    return airplane;
}

bool Flight::isHostInList(Host* h)
{
    foreach (Host* ho, this->hosts)
    {
        if (ho == h)
            return true;
    }
    return false;
}

bool Flight::isTicketInList(Ticket * t)
{
    foreach (Ticket* ti, this->tickets)
    {
        if (ti == t)
            return true;
    }
    return false;
}

bool Flight::isPilotSetted()
{
    return this->pilot ? true : false;
}

bool Flight::isHostEnough()
{
    return this->numOfHosts == this->hosts.size() ? true : false;
}

bool Flight::isPassengerEnough()
{
    return this->numOfPassengers >= this->capacity * 0.7 ? true : false;
}

bool Flight::isAirplaneSetted()
{
    return this->airplane ? true : false;
}

bool Flight::isDepartureCarrierSetted()
{
    return this->departure_carrier ? true : false;
}

bool Flight::isArrivalCarrierSetted()
{
    return this->arrival_carrier ? true : false;
}

void Flight::delay(qint64 milliseconds)
{
    QVector<Flight*> nexts_in_pilot_list;

    if (this->pilot)
    {
        Flight* temp = this->pilot->nextFlight(this);
        while (temp)
        {
            nexts_in_pilot_list.push_back(temp);
            temp = this->pilot->nextFlight(temp);
        }
    }
    QVector<QVector<Flight*>> host_list;
//    foreach (Host* h, this->hosts)
//    {
//        host_list.push_back(h->getList());
//    }

    for (int i = 0; i < this->hosts.size(); i++)
    {
        //host_list.push_back(this->hosts[i]->getList());
        QVector<Flight*> nexts_in_host_list;
        Flight* temp = this->hosts[i]->nextFlight(this);
        while (temp)
        {
            nexts_in_host_list.push_back(temp);
            temp = this->hosts[i]->nextFlight(temp);
        }

        host_list.push_back(nexts_in_host_list);
    }

    QVector<Flight*> nexts_in_airplane_list;

    if (this->airplane)
    {
        Flight* temp2 = this->airplane->nextFlight(this);
        while (temp2)
        {
            nexts_in_airplane_list.push_back(temp2);
            temp2 = this->airplane->nextFlight(temp2);
        }
    }

    this->setDateTimeDeparture(this->dateTimeDeparture.addMSecs(milliseconds));
    this->setDateTimeArrival(this->dateTimeArrival.addMSecs(milliseconds));

    this->setFlightState(DELAYED);

    foreach (Flight* f, nexts_in_pilot_list)
    {
        if (haveInterference(this, f))
        {
            f->delay(milliseconds);
        }
    }

    foreach (QVector<Flight*> vf, host_list)
    {
        foreach (Flight* f, vf)
        {
            if (haveInterference(this, f))
            {
                f->delay(milliseconds);
            }
        }
    }

    foreach (Flight* f, nexts_in_airplane_list)
    {
        if (haveInterference(this, f))
        {
            f->delay(milliseconds);
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
    flightState = value;
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
    if (this->flightState == DONE)
        return;

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
        this->setFlightState(DONE);
        this->pilot->attachDoneFlight(this);
        foreach (Host* h, this->hosts)
        {
            h->attachDoneFlight(this);
        }
    }
//        if ((f->getFlightState() == SUSPENDED || f->getFlightState() == DELAYED) &&
//                f->getDateTimeDeparture().msecsTo(QDateTime::currentDateTime()) <= 10 * 60 * 1000)
//        {
//            f->delay(30 * 60 * 1000);
//            f->setFlightState(DELAYED);
//        }

    else if (this->isPilotSetted() && this->isHostEnough() && this->isAirplaneSetted() &&
            this->isArrivalCarrierSetted() && this->isDepartureCarrierSetted() &&
            this->isPassengerEnough())
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

}

Flight::Flight(QString & data_str)
    : flightState(SUSPENDED), numOfPassengers(0), pilot(nullptr), airline(nullptr), airplane(nullptr), departure_carrier(nullptr), arrival_carrier(nullptr)
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
    //int i = 13;
    foreach (QString s, hosts)
    {
        this->attachHost(Recorder<Host>::getInstance()->searchByCode(s));
    }

    this->setCapacity(str_list[14].toInt());
    //this->setNumOfPassengers(str_list.at(15).toInt());

    QStringList tickets = str_list[15].split('/', Qt::SkipEmptyParts);
    foreach (QString s, tickets)
    {
        this->attachTicket(Recorder<Ticket>::getInstance()->searchByCode(s));
    }

    this->setFlightStateAsString(str_list[16]);
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
//            QString::number(this->getNumOfPassengers()) + "|";

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
//    this->search_code = s;
    this->setSearchCode(s);
//    Recorder<Flight>::getInstance()->updateFile(this);
}

//void Flight::setAirplaneSerial(const QString& s)
//{
//    this->airplaneSerial = s;
//}

void Flight::setSource(const QString & s)
{
    if (s == "")
        throw invalid_argument("Source Is Empty!");

    this->source = s;
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDestination(const QString & s)
{
    if (s == "")
        throw invalid_argument("Destination Is Empty!");

    this->destination = s;
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeArrival(const QDateTime &d)
{
    if (d <= this->dateTimeDeparture)
        throw invalid_argument("Arrival DateTime Must Be After The Departure DateTime!");

    this->dateTimeArrival.setDate(d.date());
    this->dateTimeArrival.setTime(d.time());
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeArrival(const QDateTime && d)
{
    if (d <= this->dateTimeDeparture)
        throw invalid_argument("Arrival DateTime Must Be After The Departure DateTime!");

    this->dateTimeArrival.setDate(d.date());
    this->dateTimeArrival.setTime(d.time());
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeArrival(int year, int month, int day, int hour, int minute, int second)
{
    QDate date(year, month, day);
    QTime time(hour, minute, second);
    QDateTime datetime(date, time);
    this->setDateTimeArrival(datetime);
//    this->dateTimeArrival.setDate(date);
//    this->dateTimeArrival.setTime(time);
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeDeparture(const QDateTime & d)
{
    if (d < QDateTime::currentDateTime())
        throw invalid_argument("DateTime Of This Flight Has Passed!\n"
                                 "Can Not Add This Flight!!");

    this->dateTimeDeparture.setDate(d.date());
    this->dateTimeDeparture.setTime(d.time());
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeDeparture(const QDateTime && d)
{
    if (d < QDateTime::currentDateTime())
        throw invalid_argument("DateTime Of This Flight Has Passed!\n"
                                 "Can Not Add This Flight!!");

    this->dateTimeDeparture.setDate(d.date());
    this->dateTimeDeparture.setTime(d.time());
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeDeparture(int year, int month, int day, int hour, int minute, int second)
{
    QDate date(year, month, day);
    QTime time(hour, minute, second);
    QDateTime datetime(date, time);
    this->setDateTimeDeparture(datetime);
//    this->dateTimeDeparture.setDate(date);
//    this->dateTimeDeparture.setTime(time);
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setPilot(Pilot * p)
{
    if (p && !this->pilot)
    {
        this->pilot = p;

        p->attachFlight(this);
        emit flightStatusChanged();
    }
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setNumOfHosts(int n)
{
    if (n <= 0)
        throw invalid_argument("Num Of Hosts Must Be Greater Than 0!");

    this->numOfHosts = n;
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setNumOfPassengers(int n)
{
    if (n <= 0)
        throw invalid_argument("Num Of Passengers Must Be Greater Than 0!");

    this->numOfPassengers = n;
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::attachHost(Host * h)
{
//    if (!h)
//        throw QException();
    if (h && !this->isHostInList(h))
    {
        this->hosts.push_back(h);

        h->attachFlight(this);
        emit flightStatusChanged();
        //this->setFlightState()
    }
//    Recorder<Flight>::getInstance()->updateFile(this);
}


void Flight::attachTicket(Ticket * p)
{
    if (p && !this->isTicketInList(p))
    {
        this->tickets.push_back(p);
//    if (p)
//        p->setFlight(this);
        this->numOfPassengers++;
        p->setFlight(this);
        emit flightStatusChanged();
    }
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::removeHost(Host* h)
{

//    try
//    {
    this->hosts.removeOne(h);
    //this->attachHost(Recorder<Host>::getFirstFree(this));
//    this->attachHost(Recorder<Airline>::getInstance()->searchByCode(h->getAirline()->getCode())->getFirstFreeHost(this));
    this->attachHost(this->getAirline()->getFirstFreeHost(this));
//    Recorder<Flight>::getInstance()->updateFile(this);

    emit flightStatusChanged();
//    foreach (Host* h, this->getHostsList())
//    {
//        if (h == nullptr)
//        {
//            QMessageBox msg;
//            msg.setText("Not Enough Hosts!");
//            msg.exec();
//            delete this;
//            //this = nullptr;
//            return;
//        }
//    }

//        if (h == nullptr)
//        {
//            QMessageBox msg;
//            msg.setText("Not Enough Hosts!");
//            msg.exec();
//            delete this;
//            //this = nullptr;
//            Recorder<Flight>::remove(this);
//            return;
//        }
    //}
//    QMessageBox msg;
//    QString str3 = "The Flight's new Hosts Are:\n";
//    foreach (Host* h, this->getHostsList())
//    {
//        str3 += h->getFname() + " " + h->getLname() + "\n";
//    }
//    msg.setText(str3);
//    msg.exec();
//    }
//    catch (QException e)
//    {
////        Recorder<Flight>::getInstance()->updateFile(this);
//        QMessageBox msg;
//        msg.setText("Not Enough Hosts!");
//        msg.exec();
////        //this = nullptr;
//        return;
//    }
}
void Flight::removePilot(){
    //try
    //{
    this->pilot = nullptr;
    //this->attachHost(Recorder<Host>::getFirstFree(this));
//    this->setPilot(Recorder<Airline>::getInstance()->searchByCode(h->getAirline()->getCode())->getFirstFreePilot(this));
    this->setPilot(this->getAirline()->getFirstFreePilot(this));

    emit flightStatusChanged();
    //Recorder<Flight>::getInstance()->updateFile(this);
//    foreach (Host* h, this->getHostsList())
//    {
//        if (h == nullptr)
//        {
//            QMessageBox msg;
//            msg.setText("Not Enough Hosts!");
//            msg.exec();
//            delete this;
//            //this = nullptr;
//            return;
//        }
//    }

//        if (h == nullptr)
//        {
//            QMessageBox msg;
//            msg.setText("Not Enough Hosts!");
//            msg.exec();
//            delete this;
//            //this = nullptr;
//            Recorder<Flight>::remove(this);
//            return;
//        }
    //}
//    if (this->pilot)
//    {
//        QMessageBox msg;
//        QString str3 = "The Flight's new Pilot Is:\n" + this->pilot->getFname() + " " + this->pilot->getLname();
//    //    foreach (Host* h, this->getHostsList())
//    //    {
//    //        str3 += h->getFname() + " " + h->getLname() + "\n";
//    //    }
//        msg.setText(str3);
//        msg.exec();
//    }
    //}
    //catch (QException e)
    //{
//    else
//    {
//        //Recorder<Flight>::updateFile(this);
//        QMessageBox msg;
//        msg.setText("No Free Pilot Here!");
//        msg.exec();
////        delete this;
////        //this = nullptr;
//        return;
//    }
    //}
}

//void Flight::attachPassenger(Passenger * p)
//{
//    this->tickets.push_back(p);
//    if (p)
//        p->setFlight(this);
//    this->numOfPassengers--;
//}

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

Pilot *Flight::getPilot() const
{
    return this->pilot;
}

QVector<Host *> Flight::getHostsList()
{
    return this->hosts;
}

QString Flight::getSerial()
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
}

void Flight::removeCarrier(Carrier* c){
    if(c==arrival_carrier){
        arrival_carrier=Recorder<Carrier>::getInstance()->getFirstFree(getDateTimeArrival(),getDestination());
    }
    if(c==departure_carrier){
        departure_carrier=Recorder<Carrier>::getInstance()->getFirstFree(getDateTimeDeparture(),getSource());
    }
}
int Flight::getAttachedTicketsize()const{
    return tickets.size();
}
void Flight::removeTicket(Ticket* T){
   tickets.removeOne(T);
   emit flightStatusChanged();
}
bool Flight::isCheckInReady(){
    return true;
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

