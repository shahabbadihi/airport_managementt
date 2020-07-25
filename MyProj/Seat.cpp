#include "Seat.h"

void Seat::setSeatInfo(int row, int col, Airplane *a)
{
    this->row = row;
    this->column = col;
    this->airplane = a;
}

void Seat::attachTicket(Ticket* t){
    ticket=t;
}
void Seat::removeTicket(){
    ticket=nullptr;
}
Seat::Seat():ticket(nullptr){

}
bool Seat::isFree(){
    if(ticket==nullptr){return true;}
    else {return false;}
}
Ticket *Seat::getTicket(){
    return ticket;
}
