#ifndef PU2_H
#define PU2_H
#include "Passenger.h"

class PU2 : public Passenger
{
public:
    PU2();
    PU2(QString& str_data);
    ~PU2();

    void setNationalCode(long) override;
};

#endif // PU2_H
