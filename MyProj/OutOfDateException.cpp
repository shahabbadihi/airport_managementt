#include "OutOfDateException.h"

OutOfDateException::OutOfDateException(const string & s)
    : runtime_error(s)
{

}

OutOfDateException::OutOfDateException()
    : runtime_error("Out Of Date!!!")
{

}
