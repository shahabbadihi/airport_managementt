#include "p2_12.h"
#include <stdexcept>
using namespace std;

P2_12::P2_12()
{

}

P2_12::P2_12(QString &str_data)
    : Passenger(str_data)
{

}

P2_12::P2_12(qlonglong national_code, const QString &fname,
         const QString &lname, const QDate &birth,
         const QString &father_name)
    : Passenger(fname, lname, birth, father_name)
{
    this->setNationalCode(national_code);
}

double P2_12::getPrice(double base)
{
    return base * 1.5;
}

P2_12::~P2_12()
{

}

void P2_12::setNationalCode(qlonglong n)
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
    this->setSearchCode(QString::number(n) + "B");
}
