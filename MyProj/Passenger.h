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
    qlonglong nationalCode;
    QDate birthDate;
    //Ticket* ticket;
    QVector<Ticket*> list_of_tickets;
    //long ticket_no;
public:
    Passenger() {}
    Passenger(QString&);
    Passenger(const QString &fname, const QDate &birth,
              const QDate& dep_date,
              qlonglong national_code,
              const QString &lname,
              const QString &father_name);
    ~Passenger() {}

    QString get_data() override;

    void setLname(const QString&);
    void setFname(const QString&);
    void setFatherName(const QString&);
    void setNationalCode(qlonglong);
    void setBirthDate(const QDate&);
    void setBirthDate(const QDate&&);
    void setBirthDate(int year, int month, int day);
    //void setTicketNo(long);
    void attachTicket(Ticket*);
    void removeTicket(Ticket*);

    bool isTicketInList(Ticket*);
    bool isTicketListEmpty();

    QString getFname();
    QString getLname();
    QString getFatherName();
    qlonglong getNationalCode();
    QDate getBirthDate();
};

#endif // PASSENGER_H
