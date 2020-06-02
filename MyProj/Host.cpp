#include "Host.h"
#include "Airline.h"
#include <QString>

Host::Host(QString &dataStr)
{
    QStringList strList = dataStr.split('|');
    strList.replaceInStrings("\n", "");

    set_personnelCode(strList.at(0).toLong());
    setAirline(Recorder<Airline>::getInstance()->searchByCode(strList[1]));
    set_fname(strList.at(2));
    set_lname(strList.at(3));
    //set_degree(strList.at(2).toInt());
    set_nationalCode(strList.at(4).toLong());


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

    foreach (QString s, str_list_flights)
    {
        this->attachFlight(Recorder<Flight>::getInstance()->searchByCode(s));
    }
}

Host::~Host()
{
    for (int i = 0; i < this->flightListSize(); i++)
    {
       this->list[i]->removeHost(this);
    }
    this->airline->removeHost(this);
}

void Host::attachFlight(Flight * f)
{
    if (f && !this->isFlightInList(f))
    {
        this->list.push_back(f);
        f->attachHost(this);
    }
//    Recorder<Host>::getInstance()->updateFile(this);
}

void Host::setAirline(Airline *value)
{
    if (value && !this->airline)
    {
        airline = value;

        value->attachHost(this);
    }
//    Recorder<Host>::getInstance()->updateFile(this);
}
