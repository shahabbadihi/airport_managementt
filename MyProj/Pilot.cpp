#include "Pilot.h"
#include "Employee.h"
#include "Flight.h"
#include <QString>

Pilot::Pilot(QString& dataStr)
{
    QStringList strList = dataStr.split('|');
    strList.replaceInStrings("\n", "");

    set_fname(strList.at(0));
    set_lname(strList.at(1));
    set_degree(strList.at(2).toInt());
    set_nationalCode(strList.at(3).toLong());
    set_personnelCode(strList.at(4).toLong());

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
        this->attachFlight(Recorder<Flight>::searchByCode(s));
    }
}

void Pilot::attachFlight(Flight * f)
{
    this->list.push_back(f);
    Recorder<Pilot>::updateFile(this);
}

QString Pilot::get_data()
{
    QString deg;
    switch(this->degree)
    {
    case One:
        deg = "1";
        break;
    case Two:
        deg = "2";
        break;
    case Three:
        deg = "3";
        break;
    }
    QString data = this->fname + "|" + this->lname + "|"
            + deg + "|" + QString::number(this->nationalCode) + "|"
            + QString::number(this->personnelCode) + "|"
            + QString::number(this->birthDate.month()) + "/"
            + QString::number(this->birthDate.day()) + "/" + QString::number(this->birthDate.year())
            + "|" + QString::number(this->employmentDate.month()) + "/"
            + QString::number(this->employmentDate.day()) +
            "/" + QString::number(this->employmentDate.year()) + "|";

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

void Pilot::set_degree(int deg)
{
    if (deg == 1)
        this->degree = One;
    if (deg == 2)
        this->degree = Two;
    if (deg == 3)
        this->degree = Three;
}
