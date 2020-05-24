#include "Employee.h"
#include "Flight.h"
#include <QString>
QString Employee::get_data()
{
    QString data = this->fname + "|" + this->lname + "|"
            + QString::number(this->nationalCode) + "|"
            + QString::number(this->personnelCode) + "|"
            + QString::number(this->birthDate.month()) + "/"
            + QString::number(this->birthDate.day()) + "/" + QString::number(this->birthDate.year())
            + "|" + QString::number(this->employmentDate.month()) + "/"
            + QString::number(this->employmentDate.day()) +
            "/" + QString::number(this->employmentDate.year()) + "|";
            ;
    for (int i = 0; i < this->list.size(); i++)
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
    this->search_code = QString::number(code);
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

Employee::Employee(QString &dataStr)
{
    QStringList strList = dataStr.split('|');
    strList.replaceInStrings("\n", "");

    set_fname(strList.at(0));
    set_lname(strList.at(1));
    //set_degree(strList.at(2).toInt());
    set_nationalCode(strList.at(2).toLong());
    set_personnelCode(strList.at(3).toLong());

    QStringList strListBirthDate = strList.at(4).split('/');
    QStringList strListEmpDate = strList.at(5).split('/');
    QDate birthDate(strListBirthDate.at(2).toInt(),
                    strListBirthDate.at(0).toInt(),
                    strListBirthDate.at(1).toInt());
    QDate empDate(strListEmpDate.at(2).toInt(),
                  strListEmpDate.at(0).toInt(),
                  strListEmpDate.at(1).toInt());

    set_birthDate(birthDate);
    set_employmentDate(empDate);

    QStringList str_list_flights = strList.at(6).split('/');

    foreach (QString s, str_list_flights)
    {
        this->attachFlight(Recorder<Flight>::searchByCode(s));
    }
}
int Employee::flightListSize(){
    int i =0;
    for(; i < this->list.size(); i++){}
    return i;
}
