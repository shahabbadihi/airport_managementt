#include "Passenger.h"
#include "Ticket.h"
#include <QStringList>
#include <stdexcept>
using namespace std;

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
    
    //this->setTicketNo(str_list.at(5).toLong());

    //this->setTicket(Recorder<Ticket>::getInstance()->searchByCode(str_list[5]));
    QStringList tickets = str_list[5].split('/', Qt::SkipEmptyParts);
    foreach (QString s, tickets)
    {
        this->attachTicket(Recorder<Ticket>::getInstance()->searchByCode(s));
    }
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

            //(this->ticket ? this->ticket->getSearchCode() : "") + "\n";

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
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::setFname(const QString & fname)
{
    if (fname == "")
        throw invalid_argument("First Name Is Empty!");

    this->fname = fname;
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::setFatherName(const QString & father_name)
{
    if (father_name == "")
        throw invalid_argument("Father Name Is Empty!");

    this->fatherName = father_name;
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

//void Passenger::setNationalCode(long n)
//{
//    this->nationalCode = n;
//    this->setSearchCode(QString::number(n));
//}

void Passenger::setBirthDate(const QDate & date)
{
    if (date > QDate::currentDate())
        throw invalid_argument("Invalid BirthDate!");

    this->birthDate.setDate(date.year(), date.month(), date.day());
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::setBirthDate(const QDate && date)
{
    if (date > QDate::currentDate())
        throw invalid_argument("Invalid BirthDate!");

    this->birthDate.setDate(date.year(), date.month(), date.day());
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::setBirthDate(int year, int month, int day)
{
    QDate date(year, month, day);
    this->setBirthDate(date);
//    this->birthDate.setDate(year, month, day);
    //    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::attachTicket(Ticket * t)
{
    if (t && !this->isTicketInList(t))
    {
        this->list_of_tickets.push_back(t);
        t->setPassenger(this);
    }
}

void Passenger::removeTicket(Ticket * t)
{
    if (t && this->isTicketInList(t))
    {
        this->list_of_tickets.removeOne(t);
    }
}

bool Passenger::isTicketInList(Ticket * t)
{
    foreach (Ticket* ti, this->list_of_tickets)
    {
        if (ti == t)
            return true;
    }
    return false;
}

bool Passenger::isTicketListEmpty()
{
    return this->list_of_tickets.size() ? false : true;
}

//void Passenger::setTicketNo(long n)
//{
//    this->ticket_no = n;
//    Recorder<Passenger>::getInstance()->updateFile(this);
//}

//void Passenger::setTicket(Ticket * t)
//{
//    if (t && !this->ticket)
//    {
//        this->ticket = t;
//        t->setPassenger(this);
//    }
    //this->ticket_no = t->getNo();
//    Recorder<Passenger>::getInstance()->updateFile(this);
//}

QString Passenger::getFname()
{
    return this->fname;
}

QString Passenger::getLname()
{
    return this->lname;
}

QString Passenger::getFatherName()
{
    return this->fatherName;
}

long Passenger::getNationalCode()
{
    return this->nationalCode;
}

QDate Passenger::getBirthDate()
{
    return this->birthDate;
}
