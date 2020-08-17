#include "pd3.h"
#include "Airline.h"

PD3::PD3()
{

}

PD3::PD3(QString &data_str)
    : Pilot(data_str)
{

}

PD3::PD3(qlonglong personnel_code, Airline *a, const QString &fname,
         const QString &lname, const QDate &birth_date,
         const QDate &emp_date, qlonglong national_code)
    : Pilot(personnel_code, a, fname, lname, birth_date, emp_date, national_code)
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
        data += "|";
        for (int i = 0; i < this->list_of_done_flights.size() && this->list_of_done_flights[i]; i++)
        {
            if (i == this->list_of_done_flights.size() - 1)
                data += this->list_of_done_flights.at(i)->getSerial();
            else
                data += this->list_of_done_flights.at(i)->getSerial() + "/";
        }
        data += "\n";
        return data;
}

double PD3::wage() const
{
    double kol = 0;
    float percent = 0.1;
    foreach(Flight * f, this->getDoneFlightList())
    {
        kol += f->income();
    }
    return kol * percent;
}

QString PD3::getDegreeAsString()
{
    return "Three";
}
