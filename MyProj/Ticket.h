//#pragma once
#ifndef TICKET_H
#define TICKET_H

#include <QVector>
#include <QString>
#include <QDate>
#include <QDateTime>
//#include "Price.h"
#include "Object.h"
#include "Seat.h"
class Flight;
class Airline;
class Passenger;
class Ticket : public Object
{
private:
    Flight* flight;
    Passenger* passenger;
    double price;
//    int interestRate;
    Seat * seat;
    long no;

//    void setNo(long value);
public:
    Ticket();
    Ticket(QString&);
    Ticket(long no, const QDate& birth, const QDate& dep_date,
           qlonglong national_code,
           const QString& fname, const QString& lname,
           const QString& father_name, double price, Flight * f = nullptr);
    ~Ticket() ;
    QString get_data();
    void setSeat(Seat *);
    void setPrice(double);
    void setFlight(Flight*);
    void setPassenger(Passenger*);
    Passenger *getPassenger();
    void setNo(long value);

    QString getSource();
    QString getDestination();
    Flight *getFlight() const;
    long getNo() const;
    QString getPassengerName() const;
    double  getPrice();
};


#endif // TICKET_H
