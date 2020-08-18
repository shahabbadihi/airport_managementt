#include "pd1.h"
#include "Airline.h"

PD1::PD1()
{

}

PD1::PD1(QString &data_str)
    : Pilot(data_str)
{

}

PD1::PD1(qlonglong personnel_code, Airline *a, const QString &fname,
         const QString &lname, const QDate &birth_date,
         const QDate &emp_date, qlonglong national_code)
    : Pilot(personnel_code, a, fname, lname, birth_date, emp_date, national_code)
{

}

PD1::~PD1()
{

}

QString PD1::get_data()
{
    QString data = QString::number(this->getPersonnelCode()) + "|" +
                this->getAirline()->getCode() + "|" + this->getFname() + "|" + this->getLname() + "|"
                /*+ deg + "|"*/ + "1" + "|" + QString::number(this->getNationalCode()) + "|"

                + QString::number(this->getBirthDate().month()) + "/"
                + QString::number(this->getBirthDate().day()) + "/" + QString::number(this->getBirthDate().year())
                + "|" + QString::number(this->getEmploymentDate().month()) + "/"
                + QString::number(this->getEmploymentDate().day()) +
                "/" + QString::number(this->getEmploymentDate().year()) + "|";

        for (int i = 0; i < this->getFlightList().size() && this->getFlightList()[i]; i++)
        {
            if (i == this->getFlightList().size() - 1)
                data += this->getFlightList().at(i)->getSerial();
            else
                data += this->getFlightList().at(i)->getSerial() + "/";
        }
        data += "|";
        for (int i = 0; i < this->getDoneFlightList().size() && this->getDoneFlightList()[i]; i++)
        {
            if (i == this->getDoneFlightList().size() - 1)
                data += this->getDoneFlightList().at(i)->getSerial();
            else
                data += this->getDoneFlightList().at(i)->getSerial() + "/";
        }
        data += "\n";
        return data;
}

double PD1::wage() const
{
    double kol = 0;
    float percent = 0.3;
    foreach(Flight * f, this->getDoneFlightList())
    {
        kol += f->income();
    }
    return kol * percent;
}

QString PD1::getDegreeAsString()
{
    return "One";
}
