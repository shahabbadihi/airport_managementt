#include "po12.h"

PO12::PO12()
{

}

PO12::PO12(QString &str_data)
    : Passenger(str_data)
{

}

PO12::~PO12()
{

}

void PO12::setNationalCode(long n)
{
    this->nationalCode = n;
    this->setSearchCode(QString::number(n) + "C");
}