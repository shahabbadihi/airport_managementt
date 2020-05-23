#include "Flight.h"
#include "Host.h"
#include <QString>
#include <QStringList>
Flight::Flight(QString & data_str)
{
    QStringList str_list = data_str.split('|');
    str_list.replaceInStrings("\n", "");

    this->setSerial(str_list.at(0));
    this->setSource(str_list.at(1));
    this->setDestination(str_list.at(2));

    QStringList date_departure = str_list.at(3).split('/');
    QStringList time_departure = str_list.at(4).split(':');
    QStringList date_arrival = str_list.at(5).split('/');
    QStringList time_arrival = str_list.at(6).split(':');

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

    this->setPilot(Recorder<Pilot>::searchPersonnelCode(str_list.at(7).toLong()));

    this->setNumOfHosts(str_list.at(8).toInt());

    for (int i = 9; i < 9 + this->numOfHosts; i++)
    {
        this->attachHost(Recorder<Host>::searchPersonnelCode(str_list.at(i).toLong()));
    }
}

QString Flight::get_data()
{
    QString data_str = this->serial + "|";

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
        data_str += QString::number(h->getPersonnelCode()) + "|";
    }

    data_str += "\n";

    return data_str;

}

void Flight::setSerial(const QString& s)
{
    this->serial = s;
}

void Flight::setAirplaneSerial(const QString& s)
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

void Flight::setDateTimeArrival(int year, int month, int day, int hour, int minute, int second)
{
    QDate date(year, month, day);
    QTime time(hour, minute, second);
    this->dateTimeArrival.setDate(date);
    this->dateTimeArrival.setTime(time);
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

void Flight::setDateTimeDeparture(int year, int month, int day, int hour, int minute, int second)
{
    QDate date(year, month, day);
    QTime time(hour, minute, second);
    this->dateTimeDeparture.setDate(date);
    this->dateTimeDeparture.setTime(time);
}

void Flight::setPilot(Pilot * p)
{
    this->pilot = p;
    if (p)
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
    if (h)
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

