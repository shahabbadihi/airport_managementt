#pragma once
//#ifndef TICKET_H
//#define TICKET_H

#include <QVector>
#include <QString>
#include <QDate>
#include <QDateTime>
#include "Price.h"
#include "Object.h"
class Ticket : public Object
{
private:
    long flightSerialCode;
    QDate flightDate;
    QDateTime flightTime;
    QString source;
    QString destination;
    QString passengerFname;
    QString passengerLname;
    long passengerNationalCode;
    long airplaneSerial;
    long pilotPersonnelCode;
    long deliverierCode;
    Price price;
    int interestRate;

public:

};


//#endif // TICKET_H
