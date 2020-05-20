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

    void set_fname(const QString& name)
    {
        this->fname = name;
    }
    void set_fname(const QString&& name)
    {
        this->fname = name;
    }

    void set_lname(const QString& family)
    {
        this->lname = family;
    }
    void set_lname(const QString&& family)
    {
        this->lname = family;
    }
    void set_nationalCode(long code)
    {
        this->nationalCode = code;
    }
    void set_personnelCode(long code)
    {
        this->personnelCode = code;
    }
    void set_birthDate(QDate& date)
    {
        this->birthDate.setDate(date.year(), date.month(), date.day());
    }
    void set_birthDate(QDate&& date)
    {
        this->birthDate.setDate(date.year(), date.month(), date.day());
    }
    void set_employmentDate(QDate& date)
    {
        this->employmentDate.setDate(date.year(), date.month(), date.day());
    }
    void set_employmentDate(QDate&& date)
    {
        this->employmentDate.setDate(date.year(), date.month(), date.day());
    }
    long get_personnelCode(){
        return this->personnelCode;
    }
    QString &get_name(){
        return this->fname;
    }
    QString &get_family(){
        return this->lname;
    }
};

#endif // EMPLOYEE_H
