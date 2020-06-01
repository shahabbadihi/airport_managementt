#include "Employee.h"
#include "Flight.h"
#include "Airline.h"
#include <QString>
QString Employee::get_data()
{
    QString data = QString::number(this->personnelCode) + "|"
            + (this->airline ? this->airline->getCode() : "") + "|"
            + this->fname + "|" + this->lname + "|"
            + QString::number(this->nationalCode) + "|"

            + QString::number(this->birthDate.month()) + "/"
            + QString::number(this->birthDate.day()) + "/" + QString::number(this->birthDate.year())
            + "|" + QString::number(this->employmentDate.month()) + "/"
            + QString::number(this->employmentDate.day()) +
            "/" + QString::number(this->employmentDate.year()) + "|";
            ;
    for (int i = 0; i < this->list.size() && this->list[i]; i++)
    {
        if (i == this->list.size() - 1)
            data += this->list.at(i)->getSerial();
        else
            data += this->list.at(i)->getSerial() + "/";
    }
    data += "\n";
    return data;
}

void Employee::set_fname(const QString &name)
{
    this->fname = name;
}

void Employee::set_fname(const QString &&name)
{
    this->fname = name;
}

void Employee::set_lname(const QString &family)
{
    this->lname = family;
}

void Employee::set_lname(const QString &&family)
{
    this->lname = family;
}

void Employee::set_nationalCode(long code)
{
    this->nationalCode = code;
}

void Employee::set_personnelCode(long code)
{
    this->personnelCode = code;
//    this->search_code = QString::number(code);
    this->setSearchCode(QString::number(code));
}

void Employee::set_birthDate(QDate &date)
{
    this->birthDate.setDate(date.year(), date.month(), date.day());
}

void Employee::set_birthDate(QDate &&date)
{
    this->birthDate.setDate(date.year(), date.month(), date.day());
}

void Employee::set_employmentDate(QDate &date)
{
    this->employmentDate.setDate(date.year(), date.month(), date.day());
}

void Employee::set_employmentDate(QDate &&date)
{
    this->employmentDate.setDate(date.year(), date.month(), date.day());
}

void Employee::attachFlight(Flight* f)
{
    this->list.push_back(f);
}

QString Employee::getFname()
{
    return this->fname;
}

QString Employee::getLname()
{
    return this->lname;
}

long Employee::getPersonnelCode()
{
    return this->personnelCode;
}

bool Employee::isFree(Flight* f)
{
    for (int i = 0; i < this->list.size(); i++)
    {
        if ( !(
            (this->list.at(i)->getDateTimeDeparture() > f->getDateTimeArrival() &&
             this->list.at(i)->getSource() == f->getDestination()) ||
            (this->list.at(i)->getDateTimeArrival() < f->getDateTimeDeparture() &&
             this->list.at(i)->getDestination() == f->getSource())
              )
           )
        {
            return false;
        }
    }
    return true;
}

Airline *Employee::getAirline() const
{
    return airline;
}

void Employee::setAirline(Airline *value)
{
    airline = value;
    //value->attachEmp(this);
}

Employee::Employee(QString &dataStr)
    : airline(nullptr)
{
    QStringList strList = dataStr.split('|');
    strList.replaceInStrings("\n", "");

    set_personnelCode(strList.at(0).toLong());

    set_fname(strList.at(1));
    set_lname(strList.at(2));
    //set_degree(strList.at(2).toInt());
    set_nationalCode(strList.at(3).toLong());
    setAirline(Recorder<Airline>::getInstance()->searchByCode(strList[4]));

    QStringList strListBirthDate = strList.at(5).split('/');
    QStringList strListEmpDate = strList.at(6).split('/');
    QDate birthDate(strListBirthDate.at(2).toInt(),
                    strListBirthDate.at(0).toInt(),
                    strListBirthDate.at(1).toInt());
    QDate empDate(strListEmpDate.at(2).toInt(),
                  strListEmpDate.at(0).toInt(),
                  strListEmpDate.at(1).toInt());

    set_birthDate(birthDate);
    set_employmentDate(empDate);

    QStringList str_list_flights = strList.at(7).split('/');

    foreach (QString s, str_list_flights)
    {
        this->attachFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }
}
int Employee::flightListSize(){
    int i =0;
    for(; i < this->list.size(); i++){}
    return i;
}
