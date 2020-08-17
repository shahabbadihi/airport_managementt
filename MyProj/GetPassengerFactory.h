#ifndef GETPASSENGERFACTORY_H
#define GETPASSENGERFACTORY_H
#include <QString>
#include "Passenger.h"
class GetPassengerFactory
{
public:
    GetPassengerFactory();

    static GetPassengerFactory* getInstance();

    Passenger* getPassenger(const QDate& birth, const QDate& dep_date,
                            qlonglong national_code,
                            const QString& fname, const QString& lname,
                            const QString& father_name);
    Passenger* getPassenger(QString& str_data);
private:
    static GetPassengerFactory* instance;
};

#endif // GETPASSENGERFACTORY_H
