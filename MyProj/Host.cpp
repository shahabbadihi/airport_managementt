#include "Host.h"
#include "Airline.h"
#include <QString>

extern bool ISDATACHANGED;

Host::Host(QString &dataStr)
{
    QStringList strList = dataStr.split('|');
    strList.replaceInStrings("\n", "");

    set_personnelCode(strList.at(0).toLongLong());
    setAirline(Recorder<Airline>::getInstance()->searchByCode(strList[1]));
    set_fname(strList.at(2));
    set_lname(strList.at(3));
    //set_degree(strList.at(2).toInt());
    set_nationalCode(strList.at(4).toLongLong());


    QStringList strListBirthDate = strList.at(5).split('/', Qt::SkipEmptyParts);
    QStringList strListEmpDate = strList.at(6).split('/', Qt::SkipEmptyParts);
    QDate birthDate(strListBirthDate.at(2).toInt(),
                    strListBirthDate.at(0).toInt(),
                    strListBirthDate.at(1).toInt());
    QDate empDate(strListEmpDate.at(2).toInt(),
                  strListEmpDate.at(0).toInt(),
                  strListEmpDate.at(1).toInt());

    set_birthDate(birthDate);
    set_employmentDate(empDate);

    QStringList str_list_flights = strList.at(7).split('/', Qt::SkipEmptyParts);
    QStringList str_list_done_flights = strList.at(8).split('/', Qt::SkipEmptyParts);

    foreach (QString s, str_list_flights)
    {
        this->attachFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }
    foreach (QString s, str_list_done_flights)
    {
        this->attachDoneFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }
}

Host::Host(qlonglong personnel_code, Airline *a,
           const QString &fname, const QString &lname,
           const QDate &birth_date, const QDate &emp_date,
           qlonglong national_code)
    : Employee(personnel_code, a, fname, lname, birth_date, emp_date, national_code)
{
    this->setAirline(a);
}

Host::~Host()
{
    for (int i = 0; i < this->flightListSize() && this->getFlightList()[i]; i++)
    {
       this->getFlightList()[i]->removeHost(this);
    }

    if (getAirline())
        this->getAirline()->removeHost(this);

//    Recorder<Host>::getInstance()->updateFileAll();
    ISDATACHANGED = true;
}

void Host::attachFlight(Flight * f)
{
    if (f && !this->isFlightInList(f))
    {
        Employee::attachFlight(f);
        f->attachHost(this);

//        Recorder<Host>::getInstance()->updateFileAll();
        ISDATACHANGED = true;
    }
//    Recorder<Host>::getInstance()->updateFile(this);
}

void Host::removeFlight(Flight *f)
{
    if(f && isFlightInList(f)){
        Employee::removeFlight(f);
        f->removePilot();
//        Recorder<Host>::getInstance()->updateFileAll();
        ISDATACHANGED = true;
//        QMessageBox msg;
//        msg.setText(f->getSerial()+" removed from host "+this->getFname()+ " " +this->getLname()+ "flight list");
    }
}

void Host::attachDoneFlight(Flight * f)
{
    if (f && !this->isDoneFlightInList(f) && isFlightInList(f))
    {
        Employee::attachDoneFlight(f);
//        Recorder<Host>::getInstance()->updateFileAll();
        ISDATACHANGED = true;
    }
}

void Host::removeDoneFlight(Flight *f)
{
    if(f && isDoneFlightInList(f) && isFlightInList(f)){
        Employee::removeDoneFlight(f);
//        Recorder<Host>::getInstance()->updateFileAll();
        ISDATACHANGED = true;
    }
}

void Host::setAirline(Airline *value)
{
    if (value && !this->getAirline())
    {
        Employee::setAirline(value);

        value->attachHost(this);

//        Recorder<Host>::getInstance()->updateFileAll();
        ISDATACHANGED = true;
    }
//    Recorder<Host>::getInstance()->updateFile(this);
}

double Host::wage() const
{
    double kol = 0;
    float percent = 0.05;
    foreach(Flight * f, this->getDoneFlightList())
    {
        kol += f->income();
    }
    return kol * percent;

}
