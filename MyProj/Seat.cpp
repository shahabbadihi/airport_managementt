#include "Seat.h"

void Seat::setSeatInfo(int row, int col, Airplane *a)
{
    this->row = row;
    this->column = col;
    this->airplane = a;
}

Seat::Seat()
{

}
