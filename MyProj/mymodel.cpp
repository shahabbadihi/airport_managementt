#include "mymodel.h"
#include "QAbstractItemModel"



MyModel::MyModel(QObject *parent)
    : QAbstractItemModel(parent),
      timer(new QTimer(this))
{
    //timer->setInterval(1000);
}

QModelIndex MyModel::parent(const QModelIndex &/*index*/) const
{
    return QModelIndex();
}

QModelIndex MyModel::index(int row, int column, const QModelIndex &/*parent*/) const
{
    return createIndex(row, column);
}

bool MyModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count-1);
    endInsertRows();
    return true;
}

void MyModel::recordInserted()
{
    this->insertRows(0, 1, QModelIndex());
}
//template class MyModel<Flight>;
//template class MyModel<Host>;
//template class MyModel<Pilot>;
//template class MyModel<Ticket>;
//template class MyModel<Passenger>;
//template class MyModel<Airplane>;
//template class MyModel<Airline>;
//template class MyModel<Carrier>;
