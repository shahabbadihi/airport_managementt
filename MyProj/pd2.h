#ifndef PD2_H
#define PD2_H
#include "Pilot.h"

class PD2 : public Pilot
{
public:
    PD2();
    PD2(QString& data_str);
    PD2(qlonglong personnel_code, Airline *a, const QString &fname,
             const QString &lname, const QDate &birth_date,
             const QDate &emp_date, qlonglong national_code);
    ~PD2();
    virtual double wage() const override;
    QString get_data() override;
    QString getDegreeAsString() override;
};

#endif // PD2_H
