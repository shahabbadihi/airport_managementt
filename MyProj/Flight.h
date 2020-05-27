

#ifndef FLIGHT_H
#define FLIGHT_H

#include <QString>
#include <QVector>
#include <QDate>
#include <QDateTime>

#include "Pilot.h"
class Pilot;
//#include "Passenger.h"
//class Passenger;
#include "Price.h"
//class Price;
//#include "Host.h"
#include "Object.h"
class Host;
class Ticket;
class Airline;
class Airplane;
class Carrier;
class Employee;
class Flight : public Object
{
private:
    QString serial;
    //QString airplaneSerial;
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
    //QVector<Employee*> emps;
    QVector<Ticket*> tickets;
    Airline* airline;
    Airplane* airplane;
    Carrier* carrier;
    Price ticketsSaleCost;
public:
    Flight() {}
    Flight(QString&);
    ~Flight() {}

    QString get_data();
    void setSerial(const QString&);
    void setAirplaneSerial(const QString&);
    void setSource(const QString&);
    void setDestination(const QString&);
    void setDateTimeArrival(const QDateTime&);
    void setDateTimeArrival(const QDateTime&&);
    void setDateTimeArrival(int year, int month, int day, int hour, int minute, int second);
    void setDateTimeDeparture(const QDateTime&);
    void setDateTimeDeparture(const QDateTime&&);
    void setDateTimeDeparture(int year, int month, int day, int hour, int minute, int second);
    void setPilot(Pilot*);
    void setNumOfHosts(int);
    void setNumOfPassengers(int);
    void attachHost(Host*);

    void attachTicket(Ticket*);

    void removeHost(Host*);
    //void attachPassenger(Passenger*);


    QDateTime getDateTimeArrival();
    QDateTime getDateTimeDeparture();
    QString getSource();
    QString getDestination();
    int getNumOfHosts();
    int getNumOfPassengers();
    Pilot *getPilot() const;
    QVector<Host *> getHostsList();
    QString getSerial();
    Airline *getAirline() const;
    void setAirline(Airline *value);
    void setAirplane(Airplane *value);
    Deliverier *getDeliverier() const;
    void setDeliverier(Deliverier *value);
};

#endif // FLIGHT_H
