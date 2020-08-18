#include "Host.h"
#include "Airline.h"
#include <QString>

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
{
    this->set_personnelCode(personnel_code);
    this->setAirline(a);
    this->set_fname(fname);
    this->set_lname(lname);
    this->set_birthDate(birth_date);
    this->set_employmentDate(emp_date);
    this->set_nationalCode(national_code);
}

Host::~Host()
{
    for (int i = 0; i < this->flightListSize() && this->list[i]; i++)
    {
       this->list[i]->removeHost(this);
    }

    if (airline)
        this->airline->removeHost(this);

    Recorder<Host>::getInstance()->updateFileAll();
}

void Host::attachFlight(Flight * f)
{
    if (f && !this->isFlightInList(f))
    {
        this->list.push_back(f);
        f->attachHost(this);

        Recorder<Host>::getInstance()->updateFileAll();
    }
//    Recorder<Host>::getInstance()->updateFile(this);
}

void Host::removeFlight(Flight *f)
{
    if(f && isFlightInList(f)){
        this->list.removeOne(f);
        Recorder<Host>::getInstance()->updateFileAll();
        QMessageBox msg;
        msg.setText(f->getSerial()+" removed from host "+this->getFname()+ " " +this->getLname()+ "flight list");
    }
}

void Host::attachDoneFlight(Flight * f)
{
    if (f && !this->isDoneFlightInList(f) && isFlightInList(f))
    {
        this->list_of_done_flights.push_back(f);
        Recorder<Host>::getInstance()->updateFileAll();
    }
}

void Host::removeDoneFlight(Flight *f)
{
    if(f && isDoneFlightInList(f) && isFlightInList(f)){
        this->list_of_done_flights.removeOne(f);
        Recorder<Host>::getInstance()->updateFileAll();
    }
}

void Host::setAirline(Airline *value)
{
    if (value && !this->airline)
    {
        airline = value;

        value->attachHost(this);

        Recorder<Host>::getInstance()->updateFileAll();
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
