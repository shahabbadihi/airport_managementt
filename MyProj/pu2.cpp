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
    if (count != 10)
        throw invalid_argument("National Code Must Have 10 Digits!");

    this->nationalCode = n;
    this->setSearchCode(QString::number(n) + "A");
}

