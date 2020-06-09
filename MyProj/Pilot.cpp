#include "Pilot.h"
#include "Employee.h"
#include "Flight.h"
#include <QString>
#include <Airline.h>

//QString Pilot::getDegreeAsString() const
//{
//    switch (this->degree)
//    {
//    case One:
//        return "One";
//        break;
//    case Two:
//        return "Two";
//        break;
//    case Three:
//        return "Three";
//        break;
//    }
//}

Pilot::Pilot(QString& dataStr)
{
    QStringList strList = dataStr.split('|');
    strList.replaceInStrings("\n", "");

    set_personnelCode(strList.at(0).toLong());
    setAirline(Recorder<Airline>::getInstance()->searchByCode(strList[1]));
    set_fname(strList.at(2));
    set_lname(strList.at(3));
    //set_degree(strList.at(4).toInt());
    set_nationalCode(strList.at(5).toLong());


    QStringList strListBirthDate = strList.at(6).split('/', Qt::SkipEmptyParts);
    QStringList strListEmpDate = strList.at(7).split('/', Qt::SkipEmptyParts);
    QDate birthDate(strListBirthDate.at(2).toInt(),
                    strListBirthDate.at(0).toInt(),
                    strListBirthDate.at(1).toInt());
    QDate empDate(strListEmpDate.at(2).toInt(),
                  strListEmpDate.at(0).toInt(),
                  strListEmpDate.at(1).toInt());

    set_birthDate(birthDate);
    set_employmentDate(empDate);

    QStringList str_list_flights = strList.at(8).split('/', Qt::SkipEmptyParts);

    foreach (QString s, str_list_flights)
    {
        this->attachFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }
}

void Pilot::attachFlight(Flight * f)
{
    if (f && !this->isFlightInList(f))
    {
        this->list.push_back(f);
        f->setPilot(this);
    }
//    Recorder<Pilot>::getInstance()->updateFile(this);
}
Pilot::~Pilot(){
    for (int i = 0; i < this->flightListSize(); i++)
    {
       this->list[i]->removePilot();
    }
    this->airline->removePilot(this);
}
//QString Pilot::get_data()
//{
//    QString deg;
//    switch(this->degree)
//    {
//    case One:
//        deg = "1";
//        break;
//    case Two:
//        deg = "2";
//        break;
//    case Three:
//        deg = "3";
//        break;
//    }
//    QString data = QString::number(this->personnelCode) + "|" +
//            this->airline->getCode() + "|" + this->fname + "|" + this->lname + "|"
//            /*+ deg + "|"*/ + QString::number(this->nationalCode) + "|"

//            + QString::number(this->birthDate.month()) + "/"
//            + QString::number(this->birthDate.day()) + "/" + QString::number(this->birthDate.year())
//            + "|" + QString::number(this->employmentDate.month()) + "/"
//            + QString::number(this->employmentDate.day()) +
//            "/" + QString::number(this->employmentDate.year()) + "|";

//    for (int i = 0; i < this->list.size() && this->list[i]; i++)
//    {
//        if (i == this->list.size() - 1)
//            data += this->list.at(i)->getSerial();
//        else
//            data += this->list.at(i)->getSerial() + "/";
//    }
//    data += "\n";
//    return data;
//}

void Pilot::setAirline(Airline *value)
{
    if (value && !this->airline)
    {
        airline = value;

        value->attachPilot(this);
    }
//    Recorder<Pilot>::getInstance()->updateFile(this);
}

//void Pilot::set_degree(int deg)
//{
//    if (deg == 1)
//        this->degree = One;
//    if (deg == 2)
//        this->degree = Two;
//    if (deg == 3)
//        this->degree = Three;
//    Recorder<Pilot>::getInstance()->updateFile(this);
//}
