
#ifndef SEAT_H
#define SEAT_H
#include "Airplane.h"
#include "Passenger.h"
#include "Ticket.h"
#include "Flight.h"
class Seat
{
    int row;
    int column;
    Airplane * airplane;
    void setSeatInfo(int row, int col, Airplane * a);
    QVector<Ticket*> ticket;
public:
    Seat();
    void attachTicket(Ticket*);
    void removeTicket(Ticket*);
    Ticket *getTicket(Flight*);
    int getRow(){return row;}
    int getColumn(){return column;}
    friend class Airplane;
    bool isFree(Flight*);
};

#endif // SEAT_H
