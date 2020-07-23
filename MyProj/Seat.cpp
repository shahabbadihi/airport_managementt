#include "Seat.h"

void Seat::setSeatInfo(int row, int col, Airplane *a)
{
    this->row = row;
    this->column = col;
    this->airplane = a;
}

void Seat::attachPassenger(Passenger* p){
    passenger=p;
}
void Seat::removePassenger(){
    passenger=nullptr;
}
Seat::Seat():passenger(nullptr){

}
bool Seat::isFree(){
    if(passenger==nullptr){return false;}
    else {return true;}
}
