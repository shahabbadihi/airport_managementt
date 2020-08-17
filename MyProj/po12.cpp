#include "po12.h"
#include <stdexcept>
using namespace std;

PO12::PO12()
{

}

PO12::PO12(QString &str_data)
    : Passenger(str_data)
{

}

PO12::PO12(qlonglong national_code, const QString &fname,
         const QString &lname, const QDate &birth,
         const QString &father_name)
    : Passenger(fname, lname, birth, father_name)
{
    this->setNationalCode(national_code);
}


PO12::~PO12()
{

}

void PO12::setNationalCode(qlonglong n)
{
    qlonglong c = n;
    int count = 0;
    while (c)
    {
        count++;
        c /= 10;
    }
    if (count != 10)
        throw invalid_argument("National Code Must Have 10 Digits!");

    this->nationalCode = n;
    this->setSearchCode(QString::number(n) + "C");
}
