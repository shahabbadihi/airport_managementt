#include "flighttablemodel.h"
#include "Recorder.h"
#include "Flight.h"
#include "Airline.h"
#include "Passenger.h"

template <class T>
Recorder<T>* Recorder<T>::instance;

FlightTableModel* FlightTableModel::instance;

FlightTableModel::FlightTableModel(QObject *parent)
    : MyModel(parent)
{
    connect(this->timer, SIGNAL(timeout()), this, SLOT(timerHit()));
    timer->start(1000);
}

int FlightTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return Recorder<Flight>::getInstance()->get_dataList().size();
}

int FlightTableModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 7;
}


QVariant FlightTableModel::data(const QModelIndex &index, int role) const
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

FlightTableModel* FlightTableModel::getInstance()
{
    if (instance == nullptr)
        instance = new FlightTableModel(nullptr);
    return instance;
}

void FlightTableModel::timerHit()
{
    QModelIndex left_top = createIndex(0, 0);
    QModelIndex right_down = createIndex(this->rowCount() - 1, this->columnCount() - 1);

    emit dataChanged(left_top, right_down);
    //this->insertRow()
}

//void FlightTableModel::recordInserted()
//{
//    this->insertRows(0, 1, QModelIndex());
//}


