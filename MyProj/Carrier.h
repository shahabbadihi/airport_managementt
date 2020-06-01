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
    QString place;
    //Airline* airline;
    QVector<Flight*> list_of_flights;
    QStringList list_of_missions;
public:
    Carrier() {}
    Carrier(QString&);
    ~Carrier() {}
    QString get_data();

    void attachFlight(Flight* f);
    void attachMission(const QString&);
    QString getSerial() const;
    void setSerial(const QString &value);
    //Airline *getAirline() const;
    //void setAirline(Airline *value);

    bool isFree(const QDateTime&, const QString&);
    QString getPlace() const;
    void setPlace(const QString &value);
};


#endif // CARRIER_H
