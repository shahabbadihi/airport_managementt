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
    ~Host();

    //QString get_data();
    virtual double wage() const override;

    void attachFlight(Flight *f);
    void setAirline(Airline *value);
};

#endif // HOST_H
