#ifndef PD2_H
#define PD2_H
#include "Pilot.h"

class PD2 : public Pilot
{
public:
    PD2();
    PD2(QString& data_str);
    ~PD2();
    virtual double wage();
    QString get_data() override;
    QString getDegreeAsString() override;
};

#endif // PD2_H
