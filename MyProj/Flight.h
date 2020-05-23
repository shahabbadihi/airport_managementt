

#ifndef FLIGHT_H
#define FLIGHT_H

#include <QString>
#include <QVector>
#include <QDate>
#include <QDateTime>

#include "Pilot.h"
class Pilot;
//#include "Passenger.h"
class Passenger;
#include "Price.h"
//class Price;
//#include "Host.h"
#include "Object.h"
class Host;
class Flight : public Object
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
    int numOfHosts;
    Pilot* pilot;
    QVector<Host*> hosts;
    QVector<Passenger*> passengers;
    Price ticketsSaleCost;
public:
    Flight() {}
    ~Flight() {}

    QString get_data() {}
    void setSerial(long);
    void setAirplaneSerial(long);
    void setSource(const QString&);
    void setDestination(const QString&);
    void setDateTimeArrival(const QDateTime&);
    void setDateTimeArrival(const QDateTime&&);
    void setDateTimeDeparture(const QDateTime&);
    void setDateTimeDeparture(const QDateTime&&);
    void setPilot(Pilot*);
    void setNumOfHosts(int);
    void setNumOfPassengers(int);
    void attachHost(Host*);
    void attachPassenger(Passenger*);

    QDateTime getDateTimeArrival();
    QDateTime getDateTimeDeparture();
    QString getSource();
    QString getDestination();
    int getNumOfHosts();
    int getNumOfPassengers();
    Pilot *getPilot();
    QVector<Host *> getHostsList();
};

#endif // FLIGHT_H
