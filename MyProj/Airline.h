#ifndef AIRLINE_H
#define AIRLINE_H
#include <QString>
#include <QVector>
class Host;
class Pilot;
class Employee;
class Flight;
class Airplane;
class Carrier;
#include "Object.h"
class Airline : public Object
{
public:
    Airline() {}
    Airline(const QString& name, const QString& code);
    Airline(QString&);
    ~Airline();

    QString get_data();

    void attachHost(Host*);
    void attachPilot(Pilot*);
    void attachFlight(Flight*);
    void attachAirplane(Airplane*);
    void removeHost(Host*);
    void removePilot(Pilot*);
    void removeFlight(Flight*);
    void removeAirplane(Airplane*);

    bool isFlightInList(Flight*) const;

    void setName(const QString &value);

    void setCode(const QString &value);

    QString getName() const;

    QString getCode() const;

    Pilot* getFirstFreePilot(Flight*) const;
    Host* getFirstFreeHost(Flight*) const;
    Airplane* getFirstFreeAirplane(Flight*) const;

    Flight* searchFlightByCode(QString&) const;

    QVector<Pilot*>getPilotsList() const;
    QVector<Host*>getHostsList() const;
    QVector<Flight*>getFlightsList() const;
    QVector<Airplane*>getAirplanesList() const;

private:

    QString name;
    QString code;
    QVector<Host*> list_of_hosts;
    QVector<Pilot*> list_of_pilots;
    QVector<Flight*> list_of_flights;
    QVector<Airplane*> list_of_airplanes;
};

#endif // AIRLINE_H
