#include "Passenger.h"
#include "Ticket.h"
#include <QStringList>
Passenger::Passenger(QString & data_str)
{
    QStringList str_list = data_str.split('|');
    this->setNationalCode(str_list.at(0).toLong());
    this->setFname(str_list.at(1));
    this->setLname(str_list.at(2));
    this->setFatherName(str_list.at(3));

    QStringList birth_date = str_list.at(4).split('/', Qt::SkipEmptyParts);
    this->setBirthDate(birth_date.at(2).toInt(),
                       birth_date.at(0).toInt(),
                       birth_date.at(1).toInt());
    
    //this->setTicketNo(str_list.at(5).toLong());

    this->setTicket(Recorder<Ticket>::getInstance()->searchByCode(str_list[5]));
}

QString Passenger::get_data()
{
    QString data_str = QString::number(this->nationalCode) + "|" +
            this->fname + "|" +
            this->lname + "|" +
            this->fatherName + "|" +
            QString::number(this->birthDate.month()) + "/" +
            QString::number(this->birthDate.day()) + "/" +
            QString::number(this->birthDate.year()) + "|" +

            this->ticket->getSearchCode() + "\n";
    return data_str;
}

void Passenger::setLname(const QString & lname)
{
    this->lname = lname;
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::setFname(const QString & fname)
{
    this->fname = fname;
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::setFatherName(const QString & father_name)
{
    this->fatherName = father_name;
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::setNationalCode(long n)
{
    this->nationalCode = n;
//    this->search_code = QString::number(n);
    this->setSearchCode(QString::number(n));
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::setBirthDate(const QDate & date)
{
    this->birthDate.setDate(date.year(), date.month(), date.day());
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::setBirthDate(const QDate && date)
{
    this->birthDate.setDate(date.year(), date.month(), date.day());
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

void Passenger::setBirthDate(int year, int month, int day)
{
    this->birthDate.setDate(year, month, day);
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

//void Passenger::setTicketNo(long n)
//{
//    this->ticket_no = n;
//    Recorder<Passenger>::getInstance()->updateFile(this);
//}

void Passenger::setTicket(Ticket * t)
{
    if (t && !this->ticket)
    {
        this->ticket = t;
        t->setPassenger(this);
    }
    //this->ticket_no = t->getNo();
//    Recorder<Passenger>::getInstance()->updateFile(this);
}

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
