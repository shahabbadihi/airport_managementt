//#pragma once
#ifndef PILOT_H
#define PILOT_H

#include <QVector>
#include <QString>
#include "Employee.h"
#include "Flight.h"
class Flight;
//enum Degree {One, Two, Three};

class Pilot : public Employee
{
private:
    //Degree degree;
    //QVector<Flight*> list;
public:
    Pilot() {}
    Pilot(QString& dataStr);
    ~Pilot();

    virtual QString getDegreeAsString() = 0;

    void attachFlight(Flight*);


    //void set_degree(int deg);

    //QString get_data();
    void setAirline(Airline *value);

    //QString getDegreeAsString() const;
};

#endif // PILOT_H
