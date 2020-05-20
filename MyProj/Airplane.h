#pragma once
//#ifndef AIRPLANE_H
//#define AIRPLANE_H

#include <QVector>
#include <QString>
#include "Vehicle.h"
//#include "Flight.h"
class Flight;
class Airplane : public Vehicle
{
private:
    int chairCount;
    QVector<Flight*> list;
public:

    QString& get_data()
    {
        //QString data = this->
    }
};

//#endif // AIRPLANE_H
