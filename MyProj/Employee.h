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
    qlonglong nationalCode;
    qlonglong personnelCode;
    QDate birthDate;
    QDate employmentDate;
    QVector<Flight*> list;
    QVector<Flight*> list_of_done_flights;
    Airline* airline;
public:
    Employee() : airline(nullptr) {}
//    Employee(QString& dataStr);
    Employee(qlonglong personnel_code, Airline *a, const QString &fname,
             const QString &lname, const QDate &birth_date,
             const QDate &emp_date, qlonglong national_code);
    ~Employee(){}

    QString get_data();

    virtual double wage() const = 0;


    void set_fname(const QString& name);
    void set_fname(const QString&& name);

    void set_lname(const QString& family);
    void set_lname(const QString&& family);
    void set_nationalCode(qlonglong code);
    void set_personnelCode(qlonglong code);
    void set_birthDate(const QDate& date);
    void set_birthDate(const QDate&& date);
    void set_employmentDate(const QDate& date);
    void set_employmentDate(const QDate&& date);
    void attachFlight(Flight*);
    void attachDoneFlight(Flight*);
    void removeDoneFlight(Flight * f);
    int flightListSize() const;

    QString getFname() const;
    QString getLname() const;
    qlonglong getPersonnelCode() const;

    bool isFree(Flight*) const;
    bool isFlightInList(Flight*) const;
    bool isDoneFlightInList(Flight*) const;

    Airline *getAirline() const;
    void setAirline(Airline *value);

    qlonglong getNationalCode() const;
    QDate getBirthDate() const;
    QDate getEmploymentDate() const;
    QVector<Flight *> getFlightList() const;
    QVector<Flight *> getDoneFlightList() const;


    void removeFlight(Flight*);

    Flight* prevFlight(Flight*) const;
    Flight* nextFlight(Flight*) const;
};

#endif // EMPLOYEE_H
