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

protected:
    virtual double wage();


public:
    Host() {}
    Host(QString& dataStr);
    ~Host();

    //QString get_data();

    void attachFlight(Flight *f);
    void setAirline(Airline *value);
};

#endif // HOST_H
