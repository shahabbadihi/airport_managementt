//#pragma once
#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <QVector>
#include <QString>
//#include "Vehicle.h"
//#include "Flight.h"
#include "Object.h"
class Airline;
class Flight;

class Airplane : public Object
{
private:
    int numOfSeats;
    QString serial;
    QVector<Flight*> list_of_flights;
    Airline* airline;
public:
    Airplane()  : airline(nullptr) {}
    Airplane(QString&);
    ~Airplane() {}

    QString get_data();
    int getChairCount() const;

    void attachFlight(Flight* f);

    Airline* getAirline() const;
    void setAirline(Airline *value);
    int getNumOfSeats() const;
    void setNumOfSeats(int value);
    QString getSerial() const;
    void setSerial(const QString &value);

    bool isFree(Flight*);
};

#endif // AIRPLANE_H
