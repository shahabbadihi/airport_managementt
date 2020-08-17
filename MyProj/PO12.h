#ifndef PO12_H
#define PO12_H
#include "Passenger.h"

class PO12 : public Passenger
{
public:
    PO12();
    PO12(QString& str_data);
    PO12(qlonglong national_code, const QString &fname,
         const QString &lname, const QDate &birth,
         const QString &father_name);
    ~PO12();

    void setNationalCode(qlonglong) override;
};
#endif // PO12_H
