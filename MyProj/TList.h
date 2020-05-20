#ifndef TLIST_H
#define TLIST_H
#include <QVector>
class Airplane;
class Deliverier;
class Flight;
class Host;
class Passenger;
class Pilot;
class Ticket;

template <class Z>
class TList
{
private:
    static QVector<Z*> list;
public:
    static QVector<Z*> get_list()
    {
        return list;
    }
};

#endif // TLIST_H
