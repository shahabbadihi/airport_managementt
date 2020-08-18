

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
//#include "Price.h"
//class Price;
//#include "Host.h"
#include "Object.h"
class Host;
class Ticket;
class Airline;
class Airplane;
class Carrier;
class Employee;

enum state {READY, CANCELED, SUSPENDED, DELAYED, DONE, ONAIR};

class Flight : public Object
{
    Q_OBJECT
private:
    QString serial;
    state flightState;
    //QString airplaneSerial;
    QString source;
    QString destination;
    //QDate date;
    //QTime time;
    QDateTime dateTimeDeparture;
    QDateTime dateTimeArrival;
    int numOfPassengers;
    int capacity;
    int numOfHosts;
    Pilot* pilot;
    QVector<Host*> hosts;
    //QVector<Employee*> emps;
    QVector<Ticket*> tickets;
    Airline* airline;
    Airplane* airplane;
    Carrier* departure_carrier;
    Carrier* arrival_carrier;
//    Price ticketsSaleCost;
public:
    Flight();
    Flight(QString&);
    Flight(const QString& serial, Airline * a,
           const QString& source, const QString& dest,
           const QDateTime& dp_datetime, const QDateTime& ar_datetime,
           int num_hosts, int capacity);
    ~Flight() ;

    QString get_data();
    QString getFlightStr() const;
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
    void removePilot();
    void removeAirplane();
    //void attachPassenger(Passenger*);
    void removeCarrier(Carrier*);
    void removeTicket(Ticket*);

    QDateTime getDateTimeArrival() const;
    QDateTime getDateTimeDeparture() const;
    QString getSource() const;
    QString getDestination() const;
    int getNumOfHosts() const;
    int getNumOfPassengers() const;
    Pilot *getPilot() const;
    QVector<Host *> getHostsList() const;
    QString getSerial() const;
    Airline *getAirline() const;
    void setAirline(Airline *value);
    void setAirplane(Airplane *value);
//    Carrier *getCarrier() const;
//    void setCarrier(Carrier *value);
    Carrier *getDeparture_carrier() const;
    void setDeparture_carrier(Carrier *value);
    Carrier *getArrival_carrier() const;
    void setArrival_carrier(Carrier *value);
    Airplane *getAirplane() const;

    bool isHostInList(Host*) const;
    bool isTicketInList(Ticket*) const;

    bool isPilotSetted() const;
    bool isHostEnough() const;
    bool isPassengerEnough() const;
    bool isAirplaneSetted() const;
    bool isDepartureCarrierSetted() const;
    bool isArrivalCarrierSetted() const;
    bool isCheckInReady() const;
    void delay(qint64 milliseconds);

    static bool haveInterference(Flight* f1, Flight* f2);

    int getCapacity() const;
    int getAttachedTicketsize()const;
    void setCapacity(int value);
    state getFlightState() const;
    QString getFlightStateAsString() const;
    void setFlightState(const state &value);
    void setFlightStateAsString(const QString &value);

    void setState();
    double income() const;
signals:
    void flightStatusChanged();
    void flightDoneSignal(bool);
    void flightCanceledSignal(bool);
    void flightStatusMsgSignal(const QString&);
};

#endif // FLIGHT_H
