#include "pu2.h"
#include "Ticket.h"
#include <stdexcept>
using namespace std;

PU2::PU2()
{

}

PU2::PU2(QString &str_data)
    : Passenger(str_data)
{

}

PU2::PU2(qlonglong national_code, const QString &fname,
         const QString &lname, const QDate &birth,
         const QString &father_name)
    : Passenger(fname, lname, birth, father_name)
{
    this->setNationalCode(national_code);
}

double PU2::getPrice(double base)
{
    return base * 1;
}

PU2::~PU2()
{

}

void PU2::setNationalCode(qlonglong n)
{
    qlonglong c = n;
    int count = 0;
    while (c)
    {
        count++;
        c /= 10;
    }
    if (count != 8)
        throw invalid_argument("National Code Must Have 8 Digits!");

    this->nationalCode = n;
    this->setSearchCode(QString::number(n) + "A");
}

