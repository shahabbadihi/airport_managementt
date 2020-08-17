#ifndef PU2_H
#define PU2_H
#include "Passenger.h"

class PU2 : public Passenger
{
public:
    PU2();
    PU2(QString& str_data);
    PU2(qlonglong national_code,
        const QString &fname,
        const QString &lname,
        const QDate &birth,
        const QString &father_name);
    ~PU2();

    void setNationalCode(qlonglong) override;
    double getPrice(double base) override;
};

#endif // PU2_H
