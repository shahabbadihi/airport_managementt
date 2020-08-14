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
    if (count != 10)
        throw invalid_argument("National Code Must Have 10 Digits!");

    this->nationalCode = n;
    this->setSearchCode(QString::number(n) + "B");
}
