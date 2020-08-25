#ifndef FLIGHTITEM_H
#define FLIGHTITEM_H

#include "Object.h"
class Flight;
class Airline;

class FlightItem : public Object
{
private:
    Airline* airline;
    QVector<Flight*> list_of_flights;
    QVector<Flight*> list_of_done_flights;
public:
    FlightItem() : airline(nullptr) {}
    ~FlightItem() {}
    bool isFree(Flight*) const;
    bool isFlightInList(Flight*) const;
    bool isDoneFlightInList(Flight*) const;
    Airline *getAirline() const;
    void setAirline(Airline *value);

    QVector<Flight *> getFlightList() const;
    QVector<Flight *> getDoneFlightList() const;

    void attachFlight(Flight*);
    void removeFlight(Flight*);
    void attachDoneFlight(Flight*);
    void removeDoneFlight(Flight * f);

    Flight* prevFlight(Flight*) const;
    Flight* nextFlight(Flight*) const;

protected:
    int flightListSize() const;
    int DoneFlightListSize() const;
};

#endif // FLIGHTITEM_H
