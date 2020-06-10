#ifndef PO12_H
#define PO12_H
#include "Passenger.h"

class PO12 : public Passenger
{
public:
    PO12();
    PO12(QString& str_data);
    ~PO12();
};

#endif // PO12_H
