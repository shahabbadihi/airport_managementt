#ifndef PD3_H
#define PD3_H
#include "Pilot.h"

class PD3 : public Pilot
{
public:
    PD3();
    PD3(QString& data_str);
    PD3(qlonglong personnel_code, Airline *a, const QString &fname,
             const QString &lname, const QDate &birth_date,
             const QDate &emp_date, qlonglong national_code);
    ~PD3();
    virtual double wage() const override;
    QString get_data() override;
    QString getDegreeAsString() override;
};

#endif // PD3_H
