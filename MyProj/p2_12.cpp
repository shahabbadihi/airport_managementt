#include "p2_12.h"

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

void P2_12::setNationalCode(long n)
{
    this->nationalCode = n;
    this->setSearchCode(QString::number(n) + "B");
}
