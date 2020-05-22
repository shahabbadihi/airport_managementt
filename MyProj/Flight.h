

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
    //QDate date;
    //QTime time;
    QDateTime dateTimeDeparture;
    QDateTime dateTimeArrival;
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
    void setDateTimeArrival(const QDateTime&);
    void setDateTimeArrival(const QDateTime&&);
    void setDateTimeDeparture(const QDateTime&);
    void setDateTimeDeparture(const QDateTime&&);
};

#endif // FLIGHT_H
