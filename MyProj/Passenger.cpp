#include "Passenger.h"
#include <QStringList>
Passenger::Passenger(QString & data_str)
{
    QStringList str_list = data_str.split('|');
    this->setFname(str_list.at(0));
    this->setLname(str_list.at(1));
    this->setFatherName(str_list.at(2));

    QStringList birth_date = str_list.at(3).split('/');
    this->setBirthDate(birth_date.at(2).toInt(),
                       birth_date.at(0).toInt(),
                       birth_date.at(1).toInt());
    this->setNationalCode(str_list.at(4).toLong());
}

QString Passenger::get_data()
{
    QString data_str = this->fname + "|" +
            this->lname + "|" +
            this->fatherName + "|" +
            QString::number(this->birthDate.month()) + "/" +
            QString::number(this->birthDate.day()) + "/" +
            QString::number(this->birthDate.year()) + "|" +
            QString::number(this->nationalCode) + "\n";
    return data_str;
}

void Passenger::setLname(const QString & lname)
{
    this->lname = lname;
}

void Passenger::setFname(const QString & fname)
{
    this->fname = fname;
}

void Passenger::setFatherName(const QString & father_name)
{
    this->fatherName = father_name;
}

void Passenger::setNationalCode(long n)
{
    this->nationalCode = n;
}

void Passenger::setBirthDate(const QDate & date)
{
    this->birthDate.setDate(date.year(), date.month(), date.day());
}

void Passenger::setBirthDate(const QDate && date)
{
    this->birthDate.setDate(date.year(), date.month(), date.day());
}

void Passenger::setBirthDate(int year, int month, int day)
{
    this->birthDate.setDate(year, month, day);
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
