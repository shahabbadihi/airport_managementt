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

    set_personnelCode(strList.at(0).toLongLong());
    setAirline(Recorder<Airline>::getInstance()->searchByCode(strList[1]));
    set_fname(strList.at(2));
    set_lname(strList.at(3));
    //set_degree(strList.at(4).toInt());
    set_nationalCode(strList.at(5).toLongLong());


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
    QStringList str_list_done_flights = strList.at(9).split('/', Qt::SkipEmptyParts);

    foreach (QString s, str_list_flights)
    {
        this->attachFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }
    foreach (QString s, str_list_done_flights)
    {
        this->attachDoneFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }
}

Pilot::Pilot(qlonglong personnel_code, Airline *a, const QString &fname,
             const QString &lname, const QDate &birth_date,
             const QDate &emp_date, qlonglong national_code)
    : Employee(personnel_code, a, fname, lname, birth_date, emp_date, national_code)
{
    this->setAirline(a);
}

void Pilot::attachFlight(Flight * f)
{
    if (f && !this->isFlightInList(f))
    {
        Employee::attachFlight(f);
        f->setPilot(this);
        Recorder<Pilot>::getInstance()->updateFileAll();
    }
    //    Recorder<Pilot>::getInstance()->updateFile(this);
}

void Pilot::removeFlight(Flight *f)
{
    if(f && isFlightInList(f)){
        Employee::removeFlight(f);
        f->removePilot();
        Recorder<Pilot>::getInstance()->updateFileAll();
        QMessageBox msg;
        msg.setText(f->getSerial()+" removed from pilot "+this->getFname()+ " " +this->getLname()+ "flight list");
    }
}

void Pilot::attachDoneFlight(Flight * f)
{
    if (f && !this->isDoneFlightInList(f) && isFlightInList(f))
    {
        Employee::attachDoneFlight(f);

        Recorder<Pilot>::getInstance()->updateFileAll();
    }
}

void Pilot::removeDoneFlight(Flight *f)
{
    if(f && isDoneFlightInList(f) && isFlightInList(f)){
        Employee::removeDoneFlight(f);
        Recorder<Pilot>::getInstance()->updateFileAll();
    }
}
Pilot::~Pilot(){
    for (int i = 0; i < this->flightListSize() && this->getFlightList()[i]; i++)
    {
       this->getFlightList()[i]->removePilot();
    }

    if (getAirline())
        this->getAirline()->removePilot(this);

    Recorder<Pilot>::getInstance()->updateFileAll();
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
    if (value && !this->getAirline())
    {
        Employee::setAirline(value);

        value->attachPilot(this);
        Recorder<Pilot>::getInstance()->updateFileAll();
    }
//    Recorder<Pilot>::getInstance()->updateFile(this);
}

//double Pilot::wage(double i = (Flight::income())) const
//{
//    float percent = 0.3;
//    return percent * i;

//}

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
