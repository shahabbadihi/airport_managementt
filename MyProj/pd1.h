#ifndef PD1_H
#define PD1_H
#include "Pilot.h"

class PD1 : public Pilot
{
public:
    PD1();
    PD1(QString& data_str);
    PD1(qlonglong personnel_code, Airline * a, const QString& fname,
        const QString& lname, const QDate& birth_date, const QDate& emp_date,
        qlonglong national_code);
    ~PD1();
    virtual double wage() const override;
    QString get_data() override;
    QString getDegreeAsString() override;
};

#endif // PD1_H
