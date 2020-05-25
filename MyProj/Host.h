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
    Host(QString& dataStr) : Employee(dataStr) {}
    ~Host(){
        for (int i = 0; i < this->flightListSize(); i++)
        {
           this->list[i]->removeHost(this);
        }
    }

    //QString get_data();

    void attachFlight(Flight *f);
};

#endif // HOST_H
