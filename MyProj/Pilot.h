#ifndef PILOT_H
#define PILOT_H

#include <QVector>
#include <QString>
#include "Employee.h"
#include "Flight.h"

class Pilot : public Employee
{
private:

public:
    Pilot() {}
    Pilot(QString& dataStr);
    Pilot(qlonglong personnel_code, Airline *a, const QString &fname,
           const QString &lname, const QDate &birth_date,
           const QDate &emp_date, qlonglong national_code);
    ~Pilot();

    virtual QString getDegreeAsString() = 0;

    virtual double wage() const = 0;

    void attachFlight(Flight*);

    void removeFlight(Flight* f);

    void setAirline(Airline *value);

};

#endif // PILOT_H
