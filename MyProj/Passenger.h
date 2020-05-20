#pragma once
//#ifndef PASSENGER_H
//#define PASSENGER_H
#include <QVector>
#include <QString>
#include <QDate>

#include "Object.h"

class Passenger : public Object
{
private:
    QString lname;
    QString fname;
    QString fatherName;
    long nationalCode;
    QDate birthDate;

public:

};

//#endif // PASSENGER_H
