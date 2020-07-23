#ifndef SEAT_H
#define SEAT_H
#include "Airplane.h"

class Seat
{
    int row;
    int column;
    Airplane * airplane;
    void setSeatInfo(int row, int col, Airplane * a);
public:
    Seat();
    friend class Airplane;
};

#endif // SEAT_H
