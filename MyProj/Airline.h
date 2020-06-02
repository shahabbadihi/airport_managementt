#ifndef AIRLINE_H
#define AIRLINE_H
#include <QString>
#include <QVector>
class Host;
class Pilot;
class Employee;
class Flight;
class Airplane;
//class Ticket;
class Carrier;
//class Vehicle;
#include "Object.h"
class Airline : public Object
{
public:
    Airline() {}
    Airline(const QString& name, const QString& code);
    Airline(QString&);
    ~Airline() {}

    QString get_data();

    void attachHost(Host*);
    void attachPilot(Pilot*);
    void attachFlight(Flight*);
    void attachAirplane(Airplane*);
    void removeHost(Host*);
    void removePilot(Pilot*);
    void removeFlight(Flight*);
    void removeAirplane(Airplane*);
    //void attachTicket(Ticket*);
    //void attachCarrier(Carrier*);
    void setName(const QString &value);

    void setCode(const QString &value);

    QString getName() const;

    QString getCode() const;

    Pilot* getFirstFreePilot(Flight*) const;
    Host* getFirstFreeHost(Flight*) const;
    Airplane* getFirstFreeAirplane(Flight*) const;
    //Employee* getFirstFreeEmp(Flight*) const;

    Flight* searchFlightByCode(QString&);

private:

    QString name;
    QString code;
    QVector<Host*> list_of_hosts;
    QVector<Pilot*> list_of_pilots;
    //QVector<Employee*> list_of_emps;
    QVector<Flight*> list_of_flights;
    QVector<Airplane*> list_of_airplanes;
    //QVector<Ticket*> list_of_tickets;
    //QVector<Carrier*> list_of_carriers;
    //QVector<Vehicle*> list_of_vehicles;
};

#endif // AIRLINE_H
