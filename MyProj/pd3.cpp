#include "pd3.h"
#include "Airline.h"

PD3::PD3()
{

}

PD3::PD3(QString &data_str)
    : Pilot(data_str)
{

}

PD3::~PD3()
{

}

QString PD3::get_data()
{
    QString data = QString::number(this->personnelCode) + "|" +
                this->airline->getCode() + "|" + this->fname + "|" + this->lname + "|"
                /*+ deg + "|"*/ + "3" + "|" + QString::number(this->nationalCode) + "|"

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

QString PD3::getDegreeAsString()
{
    return "Three";
}
