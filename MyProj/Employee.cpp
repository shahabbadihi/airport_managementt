#include "Employee.h"
#include "Flight.h"
#include "Airline.h"
#include <QString>

template <class T>
Recorder<T>* Recorder<T>::instance;

long Employee::getNationalCode() const
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

QVector<Flight *> Employee::getList() const
{
    return list;
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
    if (f)
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
    else if(prevFlight(f)==nullptr)
    {
        if(prevFlight(f)->getDestination()==f->getSource())return true;
        else if(prevFlight(f)->getDateTimeDeparture().secsTo(f->getDateTimeDeparture())>86400)return true;
        else return false;
    }
    else if(nextFlight(f)==nullptr)
    {
        if(nextFlight(f)->getSource()==f->getDestination())return true;
        else if(f->getDateTimeDeparture().secsTo(nextFlight(f)->getDateTimeDeparture())>86400)return true;
        else return false;
    }
    if(prevFlight(f)->getDestination()==f->getSource()&&f->getDestination()==nextFlight(f)->getSource()){
        return true;
    }
    else if(f->getDateTimeDeparture().secsTo(nextFlight(f)->getDateTimeDeparture())>86400 &&
            prevFlight(f)->getDateTimeDeparture().secsTo(f->getDateTimeDeparture())>86400)
    {
        return true;
    }
    else{
        return false;
    }
}

bool Employee::isFlightInList(Flight * f)
{
    foreach (Flight* fl, this->list)
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
Flight* Employee::nextFlight(Flight * f){
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
        if(f->getDateTimeDeparture()<this->list.at(i)->getDateTimeDeparture() &&
              next->getDateTimeDeparture()>this->list.at(i)->getDateTimeDeparture()  )
        {
            next=list.at(i);
        }
    }
    if(next->getDateTimeDeparture()<=f->getDateTimeArrival()){return f; }
    return next;
}
Flight* Employee::prevFlight(Flight * f){
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
        if(f->getDateTimeDeparture()>this->list.at(i)->getDateTimeDeparture() &&
              prev->getDateTimeDeparture()<this->list.at(i)->getDateTimeDeparture()  )
        {
            prev=list.at(i);
        }
    }
    if(prev->getDateTimeArrival()>=f->getDateTimeDeparture()){return f; }
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
int Employee::flightListSize(){
    int i =0;
    for(; i < this->list.size(); i++){}
    return i;
}
void Employee::removeFlight(Flight* f){
    if(f){
    this->list.removeOne(f);
    }
    QMessageBox msg;
    msg.setText(f->getSerial()+"removed from "+this->getFname()+this->getLname()+"flight list");
}
