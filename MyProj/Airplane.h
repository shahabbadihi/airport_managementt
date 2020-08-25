#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <QVector>
#include <QString>

#include "FlightItem.h"

class Seat;
class Airline;
#include "Flight.h"

class Airplane : public FlightItem
{
private:
    int numOfSeats;
    int num_of_rows;
    int num_of_cols;
    Seat ** seats;
    QString serial;
    void createSeats(int rows, int cols);

public:
    Airplane() {}
    Airplane(const QString & serial, Airline * airline, int rows, int cols);
    Airplane(QString&);
    ~Airplane();

    QString get_data();

    void attachFlight(Flight* f);

    void setAirline(Airline *value);
    int getNumOfSeats() const;
    void setNumOfSeats(int value);
    QString getSerial() const;
    void setSerial(const QString &value);

    void removeFlight(Flight*);

    bool isFree(Flight*) const;
    int getRowCount() const;
    int getcolumnCount() const;
    Seat * getSeat(int r,int c) const;
};

#endif // AIRPLANE_H
