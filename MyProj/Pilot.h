//#pragma once
#ifndef PILOT_H
#define PILOT_H

#include <QVector>
#include <QString>
#include "Employee.h"
//#include "Flight.h"
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
    ~Pilot();
    void attachFlight(Flight*);
    void set_degree(int deg);

    QString get_data();
    void setAirline(Airline *value);

};

#endif // PILOT_H
