#ifndef OUTOFDATEEXCEPTION_H
#define OUTOFDATEEXCEPTION_H

#include <stdexcept>
using namespace std;

class OutOfDateException : public runtime_error
{
public:
    OutOfDateException(const string&);
    OutOfDateException();

};

#endif // OUTOFDATEEXCEPTION_H
