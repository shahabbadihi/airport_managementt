//#pragma once
#ifndef PASSENGER_H
#define PASSENGER_H
#include <QVector>
#include <QString>
#include <QDate>

#include "Object.h"
class Ticket;
class Passenger : public Object
{
protected:
    QString lname;
    QString fname;
    QString fatherName;
    long nationalCode;
    QDate birthDate;
    //Ticket* ticket;
    QVector<Ticket*> list_of_tickets;
    //long ticket_no;
public:
    Passenger() {}
    Passenger(QString&);
    ~Passenger() {}

    QString get_data() override;

    void setLname(const QString&);
    void setFname(const QString&);
    void setFatherName(const QString&);
    virtual void setNationalCode(long) = 0;
    void setBirthDate(const QDate&);
    void setBirthDate(const QDate&&);
    void setBirthDate(int year, int month, int day);
    //void setTicketNo(long);
    void attachTicket(Ticket*);
    bool isTicketInList(Ticket*);

    QString getFname();
    QString getLname();
    QString getFatherName();
    long getNationalCode();
    QDate getBirthDate();
};

#endif // PASSENGER_H
