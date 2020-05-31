//#pragma once
#ifndef CARRIER_H
#define CARRIER_H

#include <QVector>
#include <QString>
#include "Object.h"
//class Vehicle;
class Flight;
class Airline;
class Carrier : public Object
{
private:
    QString serial;
    Airline* airline;
    QVector<Flight*> list_of_flights;
public:
    Carrier() {}
    Carrier(QString&);
    ~Carrier() {}
    QString get_data();

    void attachFlight(Flight* f);
    QString getSerial() const;
    void setSerial(const QString &value);
    Airline *getAirline() const;
    void setAirline(Airline *value);
};


#endif // CARRIER_H
