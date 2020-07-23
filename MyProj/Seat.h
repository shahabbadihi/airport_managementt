#ifndef SEAT_H
#define SEAT_H
#include "Airplane.h"
#include "Passenger.h"
class Seat
{
    int row;
    int column;
    Airplane * airplane;
    void setSeatInfo(int row, int col, Airplane * a);
    Passenger * passenger;
public:
    Seat();
    void attachPassenger(Passenger*);
    void removePassenger();
    friend class Airplane;
};

#endif // SEAT_H
