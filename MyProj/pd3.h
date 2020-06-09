#ifndef PD3_H
#define PD3_H
#include "Pilot.h"

class PD3 : public Pilot
{
public:
    PD3();
    PD3(QString& data_str);
    ~PD3();

    QString get_data() override;
    QString getDegreeAsString() override;
};

#endif // PD3_H
