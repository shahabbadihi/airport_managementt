//#pragma once
#ifndef TICKET_H
#define TICKET_H

#include <QVector>
#include <QString>
#include <QDate>
#include <QDateTime>
#include "Price.h"
#include "Object.h"
#include "Seat.h"
class Flight;
class Airline;
class Passenger;
class Ticket : public Object
{
private:
    //long flightSerialCode;
    //QDate flightDate;
    //QTime flightTime;
    //QDateTime flightDateTimeArrival;
    //QString source;
    //QString destination;
//    QString passengerFname;
//    QString passengerLname;
//    QString passengerFatherName;
//    QDate passengerBirthDate;
    Flight* flight;
    Passenger* passenger;
    //Airline* airline;
    //long passengerNationalCode;
    //long airplaneSerial;
    //long pilotPersonnelCode;
    //long deliverierCode;
    Price price;
    int interestRate;
    Seat * seat;
    long no;

//    void setNo(long value);
public:
    Ticket();
    Ticket(QString&);
    Ticket(long no, const QDate& birth, const QDate& dep_date,
           qlonglong national_code,
           const QString& fname, const QString& lname,
           const QString& father_name, Flight * f = nullptr);
    ~Ticket() ;
    QString get_data();
    void setSeat(Seat *);
//    void setDestination(const QString&);
//    void setSource(const QString&);
//    void setPassengerFname(const QString&);
//    void setPassengerLname(const QString&);
//    void setPassengerNationalCode(long);
//    void setDateFlight(const QDate&);
//    void setDateFlight(const QDate&&);
//    void setTimeFlight(const QTime&);
//    void setTimeFlight(const QTime&&);
//    void setDateTimeArrival(const QDateTime&);
//    void setDateTimeArrival(const QDateTime&&);
    void setFlight(Flight*);
    void setPassenger(Passenger*);
    Passenger *getPassenger();
//    void setPassengerBirthDate(const QDate&);
//    void setPassengerBirthDate(const QDate&&);
//    void setPassengerFatherName(const QString&);
    void setNo(long value);

    QString getSource();
    QString getDestination();
    //QDate getDateFlight();
    Flight *getFlight() const;
    long getNo() const;
    //void setAirline(Airline *value);
    QString getPassengerName();
    Price  getPrice();
};


#endif // TICKET_H
