#include "pu2.h"
#include "Ticket.h"

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

void PU2::setNationalCode(long n)
{
    this->nationalCode = n;
    this->setSearchCode(QString::number(n) + "A");
}

