

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
    QDateTime time;
    int numOfPassengers;
    Pilot* pilot;
    QVector<Host*> hosts;
    QVector<Passenger*> passengers;
    Price ticketsSaleCost;
public:
    QString get_data()
};

#endif // FLIGHT_H
