#include "Flight.h"
#include "Host.h"
#include "Ticket.h"
#include "Airline.h"
#include "Airplane.h"
#include "Carrier.h"
#include <QString>
#include <QStringList>
Airline *Flight::getAirline() const
{
    return airline;
}

void Flight::setAirline(Airline *value)
{
    airline = value;
    if (value)
        value->attachFlight(this);
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setAirplane(Airplane *value)
{
    airplane = value;
    if (value)
        value->attachFlight(this);
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
    departure_carrier = value;
    if (value)
    {
        value->attachFlight(this);
        value->attachMission(this->dateTimeDeparture.toString() + "DEP");
    }
//    Recorder<Flight>::getInstance()->updateFile(this);
}

Carrier *Flight::getArrival_carrier() const
{
    return arrival_carrier;
}

void Flight::setArrival_carrier(Carrier *value)
{
    arrival_carrier = value;

    if (value)
    {
        value->attachFlight(this);
        value->attachMission(this->dateTimeArrival.toString() + "ARR");
    }
//    Recorder<Flight>::getInstance()->updateFile(this);
}

Airplane *Flight::getAirplane() const
{
    return airplane;
}

Flight::Flight(QString & data_str)
     : airline(nullptr)
{
    QStringList str_list = data_str.split('|');
    str_list.replaceInStrings("\n", "");

    this->setSerial(str_list.at(0));
    this->setAirline(Recorder<Airline>::getInstance()->searchByCode(str_list[1]));
    this->setSource(str_list.at(2));
    this->setDestination(str_list.at(3));

    QStringList date_departure = str_list.at(4).split('/');
    QStringList time_departure = str_list.at(5).split(':');
    QStringList date_arrival = str_list.at(6).split('/');
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

    this->setPilot(Recorder<Pilot>::getInstance()->searchByCode(str_list.at(8)));

    this->setNumOfHosts(str_list.at(9).toInt());

    int i = 10;
    for (; i < 10 + this->numOfHosts; i++)
    {
        this->attachHost(Recorder<Host>::getInstance()->searchByCode(str_list.at(i)));
    }

    this->setNumOfPassengers(str_list.at(i).toInt());
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

    data_str += QString::number(this->pilot->getPersonnelCode()) + "|" +
            QString::number(this->numOfHosts) + "|";

    foreach (Host* h, this->hosts)
    {
        if (h)
            data_str += QString::number(h->getPersonnelCode()) + "|";
    }

    data_str += QString::number(this->getNumOfPassengers()) + "\n";

    return data_str;

}

void Flight::setSerial(const QString& s)
{
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
    this->source = s;
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDestination(const QString & s)
{
    this->destination = s;
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeArrival(const QDateTime &d)
{
    this->dateTimeArrival.setDate(d.date());
    this->dateTimeArrival.setTime(d.time());
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeArrival(const QDateTime && d)
{
    this->dateTimeArrival.setDate(d.date());
    this->dateTimeArrival.setTime(d.time());
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeArrival(int year, int month, int day, int hour, int minute, int second)
{
    QDate date(year, month, day);
    QTime time(hour, minute, second);
    this->dateTimeArrival.setDate(date);
    this->dateTimeArrival.setTime(time);
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeDeparture(const QDateTime & d)
{
    this->dateTimeDeparture.setDate(d.date());
    this->dateTimeDeparture.setTime(d.time());
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeDeparture(const QDateTime && d)
{
    this->dateTimeDeparture.setDate(d.date());
    this->dateTimeDeparture.setTime(d.time());
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setDateTimeDeparture(int year, int month, int day, int hour, int minute, int second)
{
    QDate date(year, month, day);
    QTime time(hour, minute, second);
    this->dateTimeDeparture.setDate(date);
    this->dateTimeDeparture.setTime(time);
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setPilot(Pilot * p)
{
    this->pilot = p;
    if (p)
        p->attachFlight(this);
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setNumOfHosts(int n)
{
    this->numOfHosts = n;
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::setNumOfPassengers(int n)
{
    this->numOfPassengers = n;
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::attachHost(Host * h)
{
//    if (!h)
//        throw QException();
    this->hosts.push_back(h);
    if (h)
        h->attachFlight(this);
//    Recorder<Flight>::getInstance()->updateFile(this);
}


void Flight::attachTicket(Ticket * p)
{
    this->tickets.push_back(p);
//    if (p)
//        p->setFlight(this);
    this->numOfPassengers--;
//    Recorder<Flight>::getInstance()->updateFile(this);
}

void Flight::removeHost(Host* h)
{

    try
    {
    this->hosts.removeOne(h);
    //this->attachHost(Recorder<Host>::getFirstFree(this));
//    this->attachHost(Recorder<Airline>::getInstance()->searchByCode(h->getAirline()->getCode())->getFirstFreeHost(this));
    this->attachHost(this->getAirline()->getFirstFreeHost(this));
    Recorder<Flight>::getInstance()->updateFile(this);
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
    QMessageBox msg;
    QString str3 = "The Flight's new Hosts Are:\n";
    foreach (Host* h, this->getHostsList())
    {
        str3 += h->getFname() + " " + h->getLname() + "\n";
    }
    msg.setText(str3);
    msg.exec();
    }
    catch (QException e)
    {
        Recorder<Flight>::getInstance()->updateFile(this);
        QMessageBox msg;
        msg.setText("Not Enough Hosts!");
        msg.exec();
//        delete this;
//        //this = nullptr;
        return;
    }
}
void Flight::removePilot(Pilot* h){
    //try
    //{
    this->pilot = nullptr;
    //this->attachHost(Recorder<Host>::getFirstFree(this));
//    this->setPilot(Recorder<Airline>::getInstance()->searchByCode(h->getAirline()->getCode())->getFirstFreePilot(this));
    this->setPilot(this->getAirline()->getFirstFreePilot(this));
    Recorder<Flight>::getInstance()->updateFile(this);
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
    if (this->pilot)
    {
        QMessageBox msg;
        QString str3 = "The Flight's new Pilot Is:\n" + this->pilot->getFname() + " " + this->pilot->getLname();
    //    foreach (Host* h, this->getHostsList())
    //    {
    //        str3 += h->getFname() + " " + h->getLname() + "\n";
    //    }
        msg.setText(str3);
        msg.exec();
    }
    //}
    //catch (QException e)
    //{
    else
    {
        //Recorder<Flight>::updateFile(this);
        QMessageBox msg;
        msg.setText("No Free Pilot Here!");
        msg.exec();
//        delete this;
//        //this = nullptr;
        return;
    }
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

