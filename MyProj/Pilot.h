//#pragma once
#ifndef PILOT_H
#define PILOT_H

#include <QVector>
#include <QString>
#include "Employee.h"
#include "Flight.h"
class Flight;
class Pilot : public Employee
{
private:
    enum Degree {One, Two, Three};
    Degree degree;
    //QVector<Flight*> list;
public:
    Pilot() {}
    Pilot(QString& dataStr);
    ~Pilot(){
        for (int i = 0; i < this->flightListSize(); i++)
        {
           this->list[i]->removePilot(this);
        }
    }

    void set_degree(int deg);

    QString get_data();


};

#endif // PILOT_H
