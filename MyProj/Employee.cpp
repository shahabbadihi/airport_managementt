#include "Employee.h"
#include "Flight.h"
#include "Airline.h"
#include <QString>
#include <stdexcept>
using namespace std;

qlonglong Employee::getNationalCode() const
{
    return nationalCode;
}

QDate Employee::getBirthDate() const
{
    return birthDate;
}

//double Employee::wage() const
//{
    //double kol;
    //float percent;
    //foreach(Flight * f, this->getDoneFlightList())
    //{
        //kol += f->income();
    //}
    //return kol;
//}

QDate Employee::getEmploymentDate() const
{
    return employmentDate;
}

QVector<Flight *> Employee::getFlightList() const
{
    return list;
}

QVector<Flight *> Employee::getDoneFlightList() const
{
    return this->list_of_done_flights;
}

Employee::Employee(qlonglong personnel_code, Airline *a, const QString &fname,
                   const QString &lname, const QDate &birth_date,
                   const QDate &emp_date, qlonglong national_code)
    : airline(nullptr)
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
    data += "|";
    for (int i = 0; i < this->list_of_done_flights.size() && this->list_of_done_flights[i]; i++)
    {
        if (i == this->list_of_done_flights.size() - 1)
            data += this->list_of_done_flights.at(i)->getSerial();
        else
            data += this->list_of_done_flights.at(i)->getSerial() + "/";
    }

    data += "\n";
    return data;
}

void Employee::set_fname(const QString &name)
{
    if (name == "")
        throw invalid_argument("First Name Is Empty!");
    this->fname = name;
}

void Employee::set_fname(const QString &&name)
{
    if (name == "")
        throw invalid_argument("First Name Is Empty!");
    this->fname = name;
}

void Employee::set_lname(const QString &family)
{
    if (family == "")
        throw invalid_argument("Last Name Is Empty!");
    this->lname = family;
}

void Employee::set_lname(const QString &&family)
{
    if (family == "")
        throw invalid_argument("Last Name Is Empty!");
    this->lname = family;
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
}
void Employee::set_personnelCode(qlonglong code)
{
    if (code <= 0)
        throw invalid_argument("Invalid Value For Personnel Code!");

    this->personnelCode = code;
//    this->search_code = QString::number(code);
    this->setSearchCode(QString::number(code));
}

void Employee::set_birthDate(const QDate &date)
{
    if (date > QDate::currentDate())
        throw invalid_argument("Invalid BirthDate!");

    this->birthDate.setDate(date.year(), date.month(), date.day());
}

void Employee::set_birthDate(const QDate &&date)
{
    if (date > QDate::currentDate())
        throw invalid_argument("Invalid BirthDate!");

    this->birthDate.setDate(date.year(), date.month(), date.day());
}

void Employee::set_employmentDate(const QDate &date)
{
    if (date < this->birthDate)
        throw invalid_argument("Invalid Employment Date!\nMust Be After The BirthDay!!!");

    this->employmentDate.setDate(date.year(), date.month(), date.day());
}

void Employee::set_employmentDate(const QDate &&date)
{
    if (date < this->birthDate)
        throw invalid_argument("Invalid Employment Date!\nMust Be After The BirthDay!!!");

    this->employmentDate.setDate(date.year(), date.month(), date.day());
}

void Employee::attachFlight(Flight* f)
{
    if (f && !this->isFlightInList(f))
    {
        this->list.push_back(f);
    }
}

void Employee::attachDoneFlight(Flight * f)
{
    if (f && !this->isDoneFlightInList(f) && isFlightInList(f))
    {
        this->list_of_done_flights.push_back(f);
    }
}

void Employee::removeDoneFlight(Flight * f)
{
    if(f && isDoneFlightInList(f) && isFlightInList(f)){
    this->list_of_done_flights.removeOne(f);
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
    if(isFlightInList(f))
    {
        return false;
    }
    if(prevFlight(f)==f || nextFlight(f)==f)
    {
        return false;
    }
    if(prevFlight(f)==nullptr&&nextFlight(f)==nullptr)
    {
        return true;
    }
    else if(nextFlight(f)==nullptr)
    {
        if(prevFlight(f)->getDestination()==f->getSource())return true;
        else if(prevFlight(f)->getDateTimeDeparture().secsTo(f->getDateTimeDeparture())>86400)return true;
        else return false;
    }
    else if(prevFlight(f)==nullptr)
    {
        if(nextFlight(f)->getSource()==f->getDestination())return true;
        else if(f->getDateTimeDeparture().secsTo(nextFlight(f)->getDateTimeDeparture())>86400)return true;
        else return false;
    }

    if(prevFlight(f)->getDestination()==f->getSource()&&f->getDestination()==nextFlight(f)->getSource()){
        return true;
    }
    else if((f->getDateTimeDeparture().secsTo(nextFlight(f)->getDateTimeDeparture())>24 * 60 * 60 &&
            f->getDestination() != nextFlight(f)->getSource()) ||
            ((prevFlight(f)->getDateTimeDeparture().secsTo(f->getDateTimeDeparture())>24 * 60 * 60) &&
             f->getSource() == prevFlight(f)->getDestination()))
    {
        return true;
    }
    else{
        return false;
    }
}

bool Employee::isFlightInList(Flight * f) const
{
    foreach (Flight* fl, this->list)
    {
        if (fl == f)
            return true;
    }
    return false;
}

bool Employee::isDoneFlightInList(Flight * f) const
{
    foreach (Flight* fl, this->list_of_done_flights)
    {
        if (fl == f)
            return true;
    }
    return false;
}

Airline *Employee::getAirline() const
{
    return airline;
}

void Employee::setAirline(Airline *value)
{
    if (value && !this->airline)
    {
        airline = value;
    }
}

Flight* Employee::nextFlight(Flight * f) const{
    if(list.size()==0){return nullptr;}
    Flight* next = nullptr;
    for (int i = 0; i < this->list.size(); i++)
    {
        if(f->getDateTimeDeparture()<this->list.at(i)->getDateTimeDeparture()){
            next=list.at(i);
        }
    }
    for (int i = 0; i < this->list.size(); i++)
    {
        if (next)
        {
            if(f->getDateTimeDeparture()<this->list.at(i)->getDateTimeDeparture() &&
                  next->getDateTimeDeparture()>this->list.at(i)->getDateTimeDeparture()  )
            {
                next=list.at(i);
            }
        }
    }

    if (next)
    {
        if(next->getDateTimeDeparture()<=f->getDateTimeArrival()){return f; }
    }
    return next;
}

Flight* Employee::prevFlight(Flight * f) const{
    if(list.size()==0){return nullptr;}
    Flight* prev = nullptr;
    for (int i = 0; i < this->list.size(); i++)
    {
        if(f->getDateTimeDeparture()>this->list.at(i)->getDateTimeDeparture()){
            prev=list.at(i);
        }
    }
    for (int i = 0; i < this->list.size(); i++)
    {
        if (prev)
        {
            if(f->getDateTimeDeparture()>this->list.at(i)->getDateTimeDeparture() &&
                  prev->getDateTimeDeparture()<this->list.at(i)->getDateTimeDeparture()  )
            {
                prev=list.at(i);
            }
        }
    }

    if (prev)
    {
        if(prev->getDateTimeArrival()>=f->getDateTimeDeparture()){return f; }
    }
    return prev;
}
//void Employee::setAirline(Airline *value)
//{
//    if (value)
//        airline = value;
//    //value->attachEmp(this);
//}

//Employee::Employee(QString &dataStr)
//    : airline(nullptr)
//{
//    QStringList strList = dataStr.split('|');
//    strList.replaceInStrings("\n", "");

//    set_personnelCode(strList.at(0).toLong());
//    setAirline(Recorder<Airline>::getInstance()->searchByCode(strList[1]));
//    set_fname(strList.at(2));
//    set_lname(strList.at(3));
//    //set_degree(strList.at(2).toInt());
//    set_nationalCode(strList.at(4).toLong());


//    QStringList strListBirthDate = strList.at(5).split('/', Qt::SkipEmptyParts);
//    QStringList strListEmpDate = strList.at(6).split('/', Qt::SkipEmptyParts);
//    QDate birthDate(strListBirthDate.at(2).toInt(),
//                    strListBirthDate.at(0).toInt(),
//                    strListBirthDate.at(1).toInt());
//    QDate empDate(strListEmpDate.at(2).toInt(),
//                  strListEmpDate.at(0).toInt(),
//                  strListEmpDate.at(1).toInt());

//    set_birthDate(birthDate);
//    set_employmentDate(empDate);

//    QStringList str_list_flights = strList.at(7).split('/', Qt::SkipEmptyParts);

//    foreach (QString s, str_list_flights)
//    {
//        this->attachFlight(Recorder<Flight>::getInstance()->searchByCode(s));
//    }
//}
int Employee::flightListSize() const{
    int i =0;
    for(; i < this->list.size(); i++){}
    return i;
}
void Employee::removeFlight(Flight* f){
    if(f){
        this->list.removeOne(f);
    }
}
