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
    Passenger(const QString &fname,
              const QString &lname, const QDate &birth,
              const QString &father_name);
    ~Passenger() {}

    QString get_data() override;

    void setLname(const QString&);
    void setFname(const QString&);
    void setFatherName(const QString&);
    virtual void setNationalCode(qlonglong) = 0;
    virtual double getPrice(double base) = 0;
    void setBirthDate(const QDate&);
    void setBirthDate(const QDate&&);
    void setBirthDate(int year, int month, int day);
    //void setTicketNo(long);
    void attachTicket(Ticket*);
    void removeTicket(Ticket*);

    bool isTicketInList(Ticket*) const;
    bool isTicketListEmpty() const;

    QString getFname() const;
    QString getLname() const;
    QString getFatherName() const;
    qlonglong getNationalCode() const;
    QDate getBirthDate() const;
};

#endif // PASSENGER_H
