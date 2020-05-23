#pragma once
//#ifndef TICKET_H
//#define TICKET_H

#include <QVector>
#include <QString>
#include <QDate>
#include <QDateTime>
#include "Price.h"
#include "Object.h"
class Flight;
class Ticket : public Object
{
private:
    long flightSerialCode;
    QDate flightDate;
    QTime flightTime;
    QDateTime flightDateTimeArrival;
    QString source;
    QString destination;
    QString passengerFname;
    QString passengerLname;
    QString passengerFatherName;
    QDate passengerBirthDate;
    Flight* flight;
    Passenger* passenger;
    long passengerNationalCode;
    long airplaneSerial;
    long pilotPersonnelCode;
    long deliverierCode;
    Price price;
    int interestRate;

public:
    Ticket() : flight(nullptr), passenger(nullptr) {}
    ~Ticket() {}
    QString get_data();

    void setDestination(const QString&);
    void setSource(const QString&);
    void setPassengerFname(const QString&);
    void setPassengerLname(const QString&);
    void setPassengerNationalCode(long);
    void setDateFlight(const QDate&);
    void setDateFlight(const QDate&&);
    void setTimeFlight(const QTime&);
    void setTimeFlight(const QTime&&);
    void setDateTimeArrival(const QDateTime&);
    void setDateTimeArrival(const QDateTime&&);
    void setFlight(Flight*);
    void setPassenger(Passenger*);
    void setPassengerBirthDate(const QDate&);
    void setPassengerBirthDate(const QDate&&);
    void setPassengerFatherName(const QString&);

    QString getSource();
    QString getDestination();
    QDate getDateFlight();
    Flight *getFlight() const;
};


//#endif // TICKET_H
