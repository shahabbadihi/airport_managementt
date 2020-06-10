#ifndef P2_12_H
#define P2_12_H
#include "Passenger.h"

class P2_12 : public Passenger
{
public:
    P2_12();
    P2_12(QString& str_data);
    ~P2_12();

    void setNationalCode(long) override;
};

#endif // P2_12_H
