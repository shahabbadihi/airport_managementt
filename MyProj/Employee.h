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
    Airline* airline;
    QString defaultLocation;
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
    void set_defaultLocation(QString & loc);
    void set_defaultLocation(QString && loc);
    void attachFlight(Flight*);
    int flightListSize();

    QString getFname();
    QString getLname();
    long getPersonnelCode();
    QString getDefaultLocation();

    bool isFree(Flight*);
    bool isFlightInList(Flight*);

    Airline *getAirline() const;
    void setAirline(Airline *value);

    long getNationalCode() const;
    QDate getBirthDate() const;
    QDate getEmploymentDate() const;
    QVector<Flight *> getList() const;


    void removeFlight(Flight*);
<<<<<<< HEAD

=======
>>>>>>> 2eb885eec09563e0fcf079f15360311dab25deef
};

#endif // EMPLOYEE_H
