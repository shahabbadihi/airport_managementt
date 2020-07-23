//#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QVector>

//#include "Flight.h"
#include "Object.h"
class Flight;
class Airline;
class Employee : public Object
{
protected:
    QString fname;
    QString lname;
    long nationalCode;
    long personnelCode;
    QDate birthDate;
    QDate employmentDate;
    QVector<Flight*> list;
    QVector<Flight*> list_of_done_flights;
    Airline* airline;
public:
    Employee() : airline(nullptr) {}
    Employee(QString& dataStr);
    ~Employee(){}

    QString get_data();


    void set_fname(const QString& name);
    void set_fname(const QString&& name);

    void set_lname(const QString& family);
    void set_lname(const QString&& family);
    void set_nationalCode(long code);
    void set_personnelCode(long code);
    void set_birthDate(QDate& date);
    void set_birthDate(QDate&& date);
    void set_employmentDate(QDate& date);
    void set_employmentDate(QDate&& date);
    void attachFlight(Flight*);
    void attachDoneFlight(Flight*);
    void removeDoneFlight(Flight * f);
    int flightListSize();

    QString getFname();
    QString getLname();
    long getPersonnelCode();

    bool isFree(Flight*);
    bool isFlightInList(Flight*);

    Airline *getAirline() const;
    void setAirline(Airline *value);

    long getNationalCode() const;
    QDate getBirthDate() const;
    QDate getEmploymentDate() const;
    QVector<Flight *> getFlightList() const;
    QVector<Flight *> getDoneFlightList() const;


    void removeFlight(Flight*);

    Flight* prevFlight(Flight*);
    Flight* nextFlight(Flight*);
};

#endif // EMPLOYEE_H
