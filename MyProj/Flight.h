

#ifndef FLIGHT_H
#define FLIGHT_H

#include <QString>
#include <QVector>
#include <QDate>
#include <QDateTime>

//#include "Pilot.h"
class Pilot;
//#include "Passenger.h"
class Passenger;
#include "Price.h"
//class Price;
//#include "Host.h"
#include "Object.h"
class Host;
class Flight : Object
{
private:
    QString serial;
    QString airplaneSerial;
    QString source;
    QString destination;
    QDate date;
    QTime time;
    int numOfPassengers;
    Pilot* pilot;
    QVector<Host*> hosts;
    QVector<Passenger*> passengers;
    Price ticketsSaleCost;
public:
    QString get_data();
    void setSerial(long);
    void setAirplaneSerial(long);
    void setSource(const QString&);
    void setDestination(const QString&);
    void setDate(const QDate&);
    void setDate(const QDate&&);
    void setDate(int year, int month, int day);
    void setTime(const QTime&);
    void setTime(const QTime&&);
    void setTime(int hour, int minute, int second);
};

#endif // FLIGHT_H
