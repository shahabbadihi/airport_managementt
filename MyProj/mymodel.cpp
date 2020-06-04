#include "mymodel.h"
#include "QAbstractItemModel"
#include "Recorder.h"
#include "Flight.h"
#include "Airline.h"

template <class T>
Recorder<T>* Recorder<T>::instance;

MyModel* MyModel::instance;

MyModel::MyModel()
{

}

MyModel::MyModel(QObject *parent)
    : QAbstractItemModel(parent),
      timer(new QTimer(this))
{
    //timer->setInterval(1000);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(timerHit()));
    timer->start(1000);
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
    return Recorder<Flight>::getInstance()->get_dataList().size();
}

int MyModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 7;
}

QModelIndex MyModel::parent(const QModelIndex &/*index*/) const
{
    return QModelIndex();
}

QModelIndex MyModel::index(int row, int column, const QModelIndex &/*parent*/) const
{
    return createIndex(row, column);
}

QVariant MyModel::data(const QModelIndex &index, int role) const
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

MyModel* MyModel::getInstance()
{
    if (instance == nullptr)
        instance = new MyModel(nullptr);
    return instance;
}

void MyModel::timerHit()
{
    QModelIndex left_top = createIndex(0, 0);
    QModelIndex right_down = createIndex(this->rowCount() - 1, this->columnCount() - 1);

    emit dataChanged(left_top, right_down);
    //this->insertRow()
}

//void MyModel::recordInserted()
//{
//    this->insertRow(0);
//}
