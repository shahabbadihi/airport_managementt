

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

enum state {READY, CANCELED, SUSPENDED, DELAYED, DONE, ONAIR};

class Flight : public Object
{
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
    Price ticketsSaleCost;
public:
    Flight()  : flightState(SUSPENDED), numOfPassengers(0), airline(nullptr), pilot(nullptr), airplane(nullptr), departure_carrier(nullptr), arrival_carrier(nullptr) {}
    Flight(QString&);
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
    //void attachPassenger(Passenger*);
    void removeCarrier(Carrier*);

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
//    Carrier *getCarrier() const;
//    void setCarrier(Carrier *value);
    Carrier *getDeparture_carrier() const;
    void setDeparture_carrier(Carrier *value);
    Carrier *getArrival_carrier() const;
    void setArrival_carrier(Carrier *value);
    Airplane *getAirplane() const;

    bool isHostInList(Host*);
    bool isTicketInList(Ticket*);

    bool isPilotSetted();
    bool isHostEnough();
    bool isPassengerEnough();
    bool isAirplaneSetted();
    bool isDepartureCarrierSetted();
    bool isArrivalCarrierSetted();

    void delay(qint64 milliseconds);

    static bool haveInterference(Flight* f1, Flight* f2);

    int getCapacity() const;
    void setCapacity(int value);
    state getFlightState() const;
    QString getFlightStateAsString() const;
    void setFlightState(const state &value);
    void setFlightStateAsString(const QString &value);
};

#endif // FLIGHT_H
