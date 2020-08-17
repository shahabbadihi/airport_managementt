#ifndef P2_12_H
#define P2_12_H
#include "Passenger.h"

class P2_12 : public Passenger
{
public:
    P2_12();
    P2_12(QString& str_data);
    P2_12(qlonglong national_code, const QString &fname,
          const QString &lname, const QDate &birth,
          const QString &father_name);
    ~P2_12();

    void setNationalCode(qlonglong) override;
    double getPrice(double base) override;
};

#endif // P2_12_H
