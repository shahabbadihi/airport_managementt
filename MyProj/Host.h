#ifndef HOST_H
#define HOST_H

#include <QVector>
#include "Employee.h"

class Host : public Employee
{
private:

public:
    Host() {}
    Host(QString& dataStr);
    Host(qlonglong personnel_code, Airline *a, const QString &fname,
         const QString &lname, const QDate &birth_date,
         const QDate &emp_date, qlonglong national_code);
    ~Host();

    virtual double wage() const override;

    void attachFlight(Flight *f);
    void setAirline(Airline *value);
    void removeFlight(Flight *f);

};

#endif // HOST_H
