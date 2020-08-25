#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QVector>

#include "FlightItem.h"

class Flight;
class Airline;
class Employee : public FlightItem
{
private:
    QString fname;
    QString lname;
    qlonglong nationalCode;
    qlonglong personnelCode;
    QDate birthDate;
    QDate employmentDate;
public:
    Employee() {}
    Employee(qlonglong personnel_code, Airline *a, const QString &fname,
             const QString &lname, const QDate &birth_date,
             const QDate &emp_date, qlonglong national_code);
    ~Employee(){}

    QString get_data();

    virtual double wage() const = 0;

protected:
    void set_birthDate(const QDate& date);
    void set_birthDate(const QDate&& date);
    void set_employmentDate(const QDate& date);
    void set_employmentDate(const QDate&& date);
    void attachFlight(Flight*);
    void removeFlight(Flight*);
    void attachDoneFlight(Flight*);
    void removeDoneFlight(Flight * f);


    void setAirline(Airline *value);

public:
    bool isFree(Flight*) const;
    qlonglong getPersonnelCode() const;
    qlonglong getNationalCode() const;
    QString getFname() const;
    QString getLname() const;
    QDate getBirthDate() const;
    QDate getEmploymentDate() const;
    void set_fname(const QString& name);
    void set_fname(const QString&& name);
    void set_lname(const QString& family);
    void set_lname(const QString&& family);
    void set_nationalCode(qlonglong code);
    void set_personnelCode(qlonglong code);

};

#endif // EMPLOYEE_H
