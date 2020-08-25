#include "Passenger.h"
#include "Ticket.h"
#include <QStringList>
#include <stdexcept>
using namespace std;

extern bool ISDATACHANGED;

Passenger::Passenger(QString & data_str)
{
    QStringList str_list = data_str.split('|');
    this->nationalCode = str_list.at(0).left(str_list[0].length() - 1).toLong();
    this->setSearchCode(str_list.at(0));
    this->setFname(str_list.at(1));
    this->setLname(str_list.at(2));
    this->setFatherName(str_list.at(3));

    QStringList birth_date = str_list.at(4).split('/', Qt::SkipEmptyParts);
    this->setBirthDate(birth_date.at(2).toInt(),
                       birth_date.at(0).toInt(),
                       birth_date.at(1).toInt());
    

    QStringList tickets = str_list[5].split('/', Qt::SkipEmptyParts);
    foreach (QString s, tickets)
    {
        this->attachTicket(Recorder<Ticket>::getInstance()->searchByCode(s));
    }
}

Passenger::Passenger(const QString &fname, const QString &lname,
                     const QDate &birth,
                     const QString &father_name)
{
    this->setFname(fname);
    this->setLname(lname);
    this->setBirthDate(birth);
    this->setFatherName(father_name);
}

QString Passenger::get_data()
{
    QString data_str = this->getSearchCode() + "|" +
            this->fname + "|" +
            this->lname + "|" +
            this->fatherName + "|" +
            QString::number(this->birthDate.month()) + "/" +
            QString::number(this->birthDate.day()) + "/" +
            QString::number(this->birthDate.year()) + "|";


    foreach (Ticket* t, this->list_of_tickets)
    {
        if (t)
            data_str += t->getSearchCode() + "/";
    }
    data_str += "\n";
    return data_str;
}

void Passenger::setLname(const QString & lname)
{
    if (lname == "")
        throw invalid_argument("Last Name Is Empty!");

    this->lname = lname;
    ISDATACHANGED = true;
}

void Passenger::setFname(const QString & fname)
{
    if (fname == "")
        throw invalid_argument("First Name Is Empty!");

    this->fname = fname;

    ISDATACHANGED = true;
}

void Passenger::setFatherName(const QString & father_name)
{
    if (father_name == "")
        throw invalid_argument("Father Name Is Empty!");

    this->fatherName = father_name;

    ISDATACHANGED = true;
}

void Passenger::setNationalCode(qlonglong n)
{
    this->nationalCode = n;
}

void Passenger::setBirthDate(const QDate & date)
{
    if (date > QDate::currentDate())
        throw invalid_argument("Invalid BirthDate!");

    this->birthDate.setDate(date.year(), date.month(), date.day());

    ISDATACHANGED = true;
}

void Passenger::setBirthDate(const QDate && date)
{
    if (date > QDate::currentDate())
        throw invalid_argument("Invalid BirthDate!");

    this->birthDate.setDate(date.year(), date.month(), date.day());

    ISDATACHANGED = true;
}

void Passenger::setBirthDate(int year, int month, int day)
{
    QDate date(year, month, day);
    this->setBirthDate(date);
}

void Passenger::attachTicket(Ticket * t)
{
    if (t && !this->isTicketInList(t))
    {
        this->list_of_tickets.push_back(t);
        t->setPassenger(this);

        ISDATACHANGED = true;
    }
}

void Passenger::removeTicket(Ticket * t)
{
    if (t && this->isTicketInList(t))
    {
        this->list_of_tickets.removeOne(t);

        ISDATACHANGED = true;
    }
}

bool Passenger::isTicketInList(Ticket * t) const
{
    foreach (Ticket* ti, this->list_of_tickets)
    {
        if (ti == t)
            return true;
    }
    return false;
}

bool Passenger::isTicketListEmpty() const
{
    return this->list_of_tickets.size() ? false : true;
}

QString Passenger::getFname() const
{
    return this->fname;
}

QString Passenger::getLname() const
{
    return this->lname;
}

QString Passenger::getFatherName() const
{
    return this->fatherName;
}

qlonglong Passenger::getNationalCode() const
{
    return this->nationalCode;
}

QDate Passenger::getBirthDate() const
{
    return this->birthDate;
}
