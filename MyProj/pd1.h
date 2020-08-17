#ifndef PD1_H
#define PD1_H
#include "Pilot.h"

class PD1 : public Pilot
{
public:
    PD1();
    PD1(QString& data_str);
    ~PD1();
    virtual double wage();
    QString get_data() override;
    QString getDegreeAsString() override;
};

#endif // PD1_H
