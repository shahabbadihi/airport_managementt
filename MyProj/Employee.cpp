#include "Employee.h"
#include "Flight.h"
#include "Airline.h"
#include <QString>
#include <stdexcept>
using namespace std;

extern bool ISDATACHANGED;

qlonglong Employee::getNationalCode() const
{
    return nationalCode;
}

QDate Employee::getBirthDate() const
{
    return birthDate;
}

QDate Employee::getEmploymentDate() const
{
    return employmentDate;
}

Employee::Employee(qlonglong personnel_code, Airline *a, const QString &fname,
                   const QString &lname, const QDate &birth_date,
                   const QDate &emp_date, qlonglong national_code)
{
    this->set_personnelCode(personnel_code);
    this->setAirline(a);
    this->set_fname(fname);
    this->set_lname(lname);
    this->set_birthDate(birth_date);
    this->set_employmentDate(emp_date);
    this->set_nationalCode(national_code);
}

QString Employee::get_data()
{
    QString data = QString::number(this->personnelCode) + "|"
            + (this->getAirline() ? this->getAirline()->getCode() : "") + "|"
            + this->fname + "|" + this->lname + "|"
            + QString::number(this->nationalCode) + "|"
            + QString::number(this->birthDate.month()) + "/"
            + QString::number(this->birthDate.day()) + "/" + QString::number(this->birthDate.year())
            + "|" + QString::number(this->employmentDate.month()) + "/"
            + QString::number(this->employmentDate.day()) +
            "/" + QString::number(this->employmentDate.year()) + "|";
            ;
    for (int i = 0; i < this->flightListSize() && this->getFlightList()[i]; i++)
    {
        if (i == this->flightListSize() - 1)
            data += this->getFlightList().at(i)->getSerial();
        else
            data += this->getFlightList().at(i)->getSerial() + "/";
    }
    data += "|";
    for (int i = 0; i < this->DoneFlightListSize() && this->getDoneFlightList()[i]; i++)
    {
        if (i == this->DoneFlightListSize() - 1)
            data += this->getDoneFlightList().at(i)->getSerial();
        else
            data += this->getDoneFlightList().at(i)->getSerial() + "/";
    }

    data += "\n";
    return data;
}

void Employee::set_fname(const QString &name)
{
    if (name == "")
        throw invalid_argument("First Name Is Empty!");
    this->fname = name;

    ISDATACHANGED = true;
}

void Employee::set_fname(const QString &&name)
{
    if (name == "")
        throw invalid_argument("First Name Is Empty!");
    this->fname = name;

    ISDATACHANGED = true;
}

void Employee::set_lname(const QString &family)
{
    if (family == "")
        throw invalid_argument("Last Name Is Empty!");
    this->lname = family;

    ISDATACHANGED = true;
}

void Employee::set_lname(const QString &&family)
{
    if (family == "")
        throw invalid_argument("Last Name Is Empty!");
    this->lname = family;

    ISDATACHANGED = true;
}

void Employee::set_nationalCode(qlonglong code)
{
    qlonglong c = code;
    int count = 0;
    while (c)
    {
        count++;
        c /= 10;
    }
    if (count != 8)
        throw invalid_argument("National Code Must Have 8 Digits!");

    this->nationalCode = code;

    ISDATACHANGED = true;
}
void Employee::set_personnelCode(qlonglong code)
{
    if (code <= 0)
        throw invalid_argument("Invalid Value For Personnel Code!");

    this->personnelCode = code;
    this->setSearchCode(QString::number(code));

    ISDATACHANGED = true;
}

void Employee::set_birthDate(const QDate &date)
{
    if (date > QDate::currentDate())
        throw invalid_argument("Invalid BirthDate!");

    this->birthDate.setDate(date.year(), date.month(), date.day());

    ISDATACHANGED = true;
}

void Employee::set_birthDate(const QDate &&date)
{
    if (date > QDate::currentDate())
        throw invalid_argument("Invalid BirthDate!");

    this->birthDate.setDate(date.year(), date.month(), date.day());

    ISDATACHANGED = true;
}

void Employee::set_employmentDate(const QDate &date)
{
    if (date < this->birthDate)
        throw invalid_argument("Invalid Employment Date!\nMust Be After The BirthDay!!!");

    this->employmentDate.setDate(date.year(), date.month(), date.day());

    ISDATACHANGED = true;
}

void Employee::set_employmentDate(const QDate &&date)
{
    if (date < this->birthDate)
        throw invalid_argument("Invalid Employment Date!\nMust Be After The BirthDay!!!");

    this->employmentDate.setDate(date.year(), date.month(), date.day());

    ISDATACHANGED = true;
}

void Employee::attachFlight(Flight* f)
{
    if (f && !this->isFlightInList(f))
    {
        FlightItem::attachFlight(f);
    }
}

void Employee::attachDoneFlight(Flight * f)
{
    if (f && !this->isDoneFlightInList(f) && isFlightInList(f))
    {
        FlightItem::attachDoneFlight(f);
    }
}

void Employee::removeDoneFlight(Flight * f)
{
    if(f && isDoneFlightInList(f) && isFlightInList(f)){
        FlightItem::removeDoneFlight(f);
    }
}

QString Employee::getFname() const
{
    return this->fname;
}

QString Employee::getLname() const
{
    return this->lname;
}

qlonglong Employee::getPersonnelCode() const
{
    return this->personnelCode;
}

bool Employee::isFree(Flight* f) const
{
    if (this->employmentDate >= f->getDateTimeDeparture().date())
    {
        return false;
    }

    return FlightItem::isFree(f);
}


void Employee::setAirline(Airline *value)
{
    FlightItem::setAirline(value);
}

void Employee::removeFlight(Flight* f){
    if(f){
        FlightItem::removeFlight(f);
    }
}
