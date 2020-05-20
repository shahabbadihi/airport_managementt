#include "Pilot.h"
#include "Employee.h"
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
            "/" + QString::number(this->employmentDate.year()) + "\n";
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
