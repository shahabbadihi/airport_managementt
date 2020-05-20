#include "Employee.h"
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
            "/" + QString::number(this->employmentDate.year()) + "\n";
    return data;
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
}
