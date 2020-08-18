//#pragma once
#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <QVector>
#include <QString>
//#include "Vehicle.h"
//#include "Flight.h"
#include "Object.h"

class Seat;
class Airline;
class Flight;

class Airplane : public Object
{
private:
    int numOfSeats;
    int num_of_rows;
    int num_of_cols;
    Seat ** seats;
    QString serial;
    QVector<Flight*> list_of_flights;
    Airline* airline;
    void createSeats(int rows, int cols);

public:
    Airplane()  : airline(nullptr) {}
    Airplane(const QString & serial, Airline * airline, int rows, int cols);
    Airplane(QString&);
    ~Airplane();

    QString get_data();
    //int getChairCount() const;

    void attachFlight(Flight* f);

    Airline* getAirline() const;
    void setAirline(Airline *value);
    int getNumOfSeats() const;
    void setNumOfSeats(int value);
    QString getSerial() const;
    void setSerial(const QString &value);

    void removeFlight(Flight*);

    bool isFree(Flight*) const;
    bool isFlightInList(Flight *f) const;
    Flight *nextFlight(Flight *f) const;
    Flight *prevFlight(Flight *f) const;
    int getRowCount() const;
    int getcolumnCount() const;
    Seat * getSeat(int r,int c) const;
    //void setSeats(int Row,int column);
    QVector<Flight *> getFlightList() const;
};

#endif // AIRPLANE_H
