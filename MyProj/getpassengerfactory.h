#ifndef GETPASSENGERFACTORY_H
#define GETPASSENGERFACTORY_H
#include <QString>
#include "Passenger.h"
class GetPassengerFactory
{
public:
    GetPassengerFactory();

    static GetPassengerFactory* getInstance();

    Passenger* getPassenger(const QDate& dt1, const QDate& dt2, const QString& search_code);
    Passenger* getPassenger(QString& str_data);
private:
    static GetPassengerFactory* instance;
};

#endif // GETPASSENGERFACTORY_H
