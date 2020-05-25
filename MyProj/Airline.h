#ifndef AIRLINE_H
#define AIRLINE_H
#include <QString>
#include <QVector>
//class Host;
//class Pilot;
class Employee;
class Flight;
class Airplane;
class Ticket;
#include "Object.h"
class Airline : public Object
{
public:
    Airline();
    Airline(const QString& name, const QString& code);
    Airline(QString&);
    ~Airline();

    QString get_data();

    //void attachHost(Host*);
    void attachEmp(Employee*);
    void attachFlight(Flight*);
    void attachAirplane(Airplane*);
    void attachTicket(Ticket*);
    void setName(const QString &value);

    void setCode(const QString &value);

    QString getName() const;

    QString getCode() const;

private:

    QString name;
    QString code;
    QVector<Employee*> list_of_emps;
    QVector<Flight*> list_of_flights;
    QVector<Airplane*> list_of_airplanes;
    QVector<Ticket*> list_of_tickets;
};

#endif // AIRLINE_H
