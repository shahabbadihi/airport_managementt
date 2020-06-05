#include "mymodel.h"
#include "QAbstractItemModel"
#include "Recorder.h"
#include "Flight.h"
#include "Airline.h"
#include "Passenger.h"

template <class T>
Recorder<T>* Recorder<T>::instance;

template <class T>
MyModel<T>* MyModel<T>::instance;

template <class T>
MyModel<T>::MyModel()
{

}

template <class T>
MyModel<T>::MyModel(QObject *parent)
    : SignalSlot(parent),
      timer(new QTimer(this))
{
    //timer->setInterval(1000);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(timerHit()));
    timer->start(1000);
}

template <class T>
int MyModel<T>::rowCount(const QModelIndex & /*parent*/) const
{
    return Recorder<Flight>::getInstance()->get_dataList().size();
}

template <class T>
int MyModel<T>::columnCount(const QModelIndex& /*parent*/) const
{
    return 7;
}

template <class T>
QModelIndex MyModel<T>::parent(const QModelIndex &/*index*/) const
{
    return QModelIndex();
}

template <class T>
QModelIndex MyModel<T>::index(int row, int column, const QModelIndex &/*parent*/) const
{
    return createIndex(row, column);
}

template <class T>
QVariant MyModel<T>::data(const QModelIndex &index, int role) const
{

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            return Recorder<Flight>::getInstance()->get_dataList()[index.row()]->getAirline()->getName();
            break;
        case 1:
            return Recorder<Flight>::getInstance()->get_dataList()[index.row()]->getSerial();
            break;
        case 2:
            return Recorder<Flight>::getInstance()->get_dataList()[index.row()]->getSource();
            break;
        case 3:
            return Recorder<Flight>::getInstance()->get_dataList()[index.row()]->getDestination();
            break;
        case 4:
            return Recorder<Flight>::getInstance()->get_dataList()[index.row()]->getDateTimeDeparture();
            break;
        case 5:
            return Recorder<Flight>::getInstance()->get_dataList()[index.row()]->getDateTimeArrival();
            break;
        case 6:
            return Recorder<Flight>::getInstance()->get_dataList()[index.row()]->getFlightStateAsString();
            break;
        }
    }
    return QVariant();
}

template <class T>
MyModel<T>* MyModel<T>::getInstance()
{
    if (instance == nullptr)
        instance = new MyModel(nullptr);
    return instance;
}

template <class T>
void MyModel<T>::timerHit()
{
    QModelIndex left_top = createIndex(0, 0);
    QModelIndex right_down = createIndex(this->rowCount() - 1, this->columnCount() - 1);

    emit dataChanged(left_top, right_down);
    //this->insertRow()
}

template <class T>
void MyModel<T>::recordInserted()
{
    this->insertRows(0, 1, QModelIndex());
}

template <class T>
bool MyModel<T>::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count-1);
    endInsertRows();
    return true;
}

template class MyModel<Flight>;
template class MyModel<Host>;
template class MyModel<Pilot>;
template class MyModel<Ticket>;
template class MyModel<Passenger>;
template class MyModel<Airplane>;
template class MyModel<Airline>;
template class MyModel<Carrier>;
