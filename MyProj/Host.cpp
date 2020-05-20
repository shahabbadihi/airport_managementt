#include "Host.h"
#include <QString>

Host::Host(QString &dataStr)
{
    QStringList strList = dataStr.split('|');
    strList.replaceInStrings("\n", "");

    set_fname(strList.at(0));
    set_lname(strList.at(1));
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
