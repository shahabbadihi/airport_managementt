#pragma once
//#ifndef VEHICLE_H
//#define VEHICLE_H
#include <QVector>
#include <QDate>
#include "Object.h"

class Vehicle : public Object
{
protected:
    long serial;
    QDate productDate;
public:

};

//#endif // VEHICLE_H
