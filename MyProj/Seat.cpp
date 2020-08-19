#include "Seat.h"

void Seat::setSeatInfo(int row, int col, Airplane *a)
{
    this->row = row;
    this->column = col;
    this->airplane = a;
}

void Seat::attachTicket(Ticket* t){
    ticket.push_back(t);
}
void Seat::removeTicket(Ticket *t){
    ticket.removeOne(t);
}
Seat::Seat(){

}
bool Seat::isFree(Flight*f){
    foreach(Ticket *t,this->ticket){
        if(t->getFlight()==f){
            return false;
        }
    }
    return true;
}
Ticket *Seat::getTicket(Flight*f){
    foreach(Ticket *t,this->ticket){
        if(t->getFlight()==f){
            return t;
        }
    }
    return nullptr;
}
