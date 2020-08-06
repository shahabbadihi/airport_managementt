#ifndef SEAT_H
#define SEAT_H
#include "Airplane.h"
#include "Passenger.h"
#include "Ticket.h"
class Seat
{
    int row;
    int column;
    Airplane * airplane;
    void setSeatInfo(int row, int col, Airplane * a);
    Ticket * ticket;
public:
    Seat();
    void attachTicket(Ticket*);
    void removeTicket();
    Ticket *getTicket();
    int getRow(){return row;}
    int getColumn(){return column;}
    friend class Airplane;
    bool isFree();
};

#endif // SEAT_H
