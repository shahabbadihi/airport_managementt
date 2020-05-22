//#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QVector>

//#include "Flight.h"
#include "Object.h"
class Flight;

class Employee : public Object
{
protected:
    QString fname;
    QString lname;
    long nationalCode;
    long personnelCode;
    QDate birthDate;
    QDate employmentDate;
    QVector<Flight*> list;
public:
    Employee(){}
    Employee(QString& dataStr);
    ~Employee(){}

    QString get_data();

    void set_fname(const QString& name);
    void set_fname(const QString&& name);

    void set_lname(const QString& family);
    void set_lname(const QString&& family);
    void set_nationalCode(long code);
    void set_personnelCode(long code);
    void set_birthDate(QDate& date);
    void set_birthDate(QDate&& date);
    void set_employmentDate(QDate& date);
    void set_employmentDate(QDate&& date);


};

#endif // EMPLOYEE_H
