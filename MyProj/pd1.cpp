#include "pd1.h"
#include "Airline.h"

PD1::PD1()
{

}

PD1::PD1(QString &data_str)
    : Pilot(data_str)
{

}

PD1::~PD1()
{

}

QString PD1::get_data()
{
    QString data = QString::number(this->personnelCode) + "|" +
                this->airline->getCode() + "|" + this->fname + "|" + this->lname + "|"
                /*+ deg + "|"*/ + "1" + "|" + QString::number(this->nationalCode) + "|"

                + QString::number(this->birthDate.month()) + "/"
                + QString::number(this->birthDate.day()) + "/" + QString::number(this->birthDate.year())
                + "|" + QString::number(this->employmentDate.month()) + "/"
                + QString::number(this->employmentDate.day()) +
                "/" + QString::number(this->employmentDate.year()) + "|";

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

QString PD1::getDegreeAsString()
{
    return "One";
}
