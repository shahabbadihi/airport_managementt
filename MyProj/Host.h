//#pragma once
#ifndef HOST_H
#define HOST_H

#include <QVector>
#include "Employee.h"
#include "Flight.h"
class Flight;
class Host : public Employee
{
private:

public:
    Host() {}
    Host(QString& dataStr);
    Host(qlonglong personnel_code, Airline *a, const QString &fname,
         const QString &lname, const QDate &birth_date,
         const QDate &emp_date, qlonglong national_code);
    ~Host();

    //QString get_data();
    virtual double wage() const override;

    void attachFlight(Flight *f);
    void setAirline(Airline *value);
    void removeFlight(Flight *f);

    void attachDoneFlight(Flight*);
    void removeDoneFlight(Flight * f);
};

#endif // HOST_H
