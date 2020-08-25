#ifndef CARRIER_H
#define CARRIER_H

#include <QVector>
#include <QString>
#include "Object.h"
class Flight;
class Airline;
class Carrier : public Object
{
private:
    QString serial;
    QString place;
    QVector<Flight*> list_of_flights;
public:
    Carrier() {}
    Carrier(QString&);
    Carrier(const QString& serial, const QString& place);
    ~Carrier() ;
    QString get_data();

    void attachFlight(Flight* f);
    QString getSerial() const;
    void setSerial(const QString &value);

    bool isFree(const QDateTime&, const QString&) const;
    bool isFlightInList(Flight*) const;
    QString getPlace() const;
    QStringList getMissionList() const;
    QString getMission(Flight* f) const;
    void setPlace(const QString &value);

    void removeFlight(Flight*);


};


#endif // CARRIER_H
