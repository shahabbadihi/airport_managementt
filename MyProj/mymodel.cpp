#include "mymodel.h"
#include "QAbstractItemModel"



MyModel::MyModel(QObject *parent)
    : QAbstractItemModel(parent),
      timer(new QTimer(this))
{
    //timer->setInterval(1000);
}


//template class MyModel<Flight>;
//template class MyModel<Host>;
//template class MyModel<Pilot>;
//template class MyModel<Ticket>;
//template class MyModel<Passenger>;
//template class MyModel<Airplane>;
//template class MyModel<Airline>;
//template class MyModel<Carrier>;
