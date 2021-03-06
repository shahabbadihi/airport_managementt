#include <QThread>
#include "flighttablemodel.h"
#include "Recorder.h"
#include "Flight.h"
#include "Airline.h"
#include "Passenger.h"
#include "ThreadedJob.h"

FlightTableModel* FlightTableModel::instance;

FlightTableModel::FlightTableModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

int FlightTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return Recorder<Flight>::getInstance()->get_dataList().size();
}

int FlightTableModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 10;
}

QModelIndex FlightTableModel::parent(const QModelIndex &/*index*/) const
{
    return QModelIndex();
}

QModelIndex FlightTableModel::index(int row, int column, const QModelIndex &/*parent*/) const
{
    return createIndex(row, column);
}

bool FlightTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count-1);
    endInsertRows();
    return true;
}

bool FlightTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
//    emit rowsAboutToBeRemoved(row);
    return true;
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

void FlightTableModel::recordInserted()
{
    int row = rowCount() - 1;
    this->insertRows(row, 1, QModelIndex());
    emit recordInsertedSignal(row);
}

QVariant FlightTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Airline");
        case 1:
            return QString("Flight Serial");
        case 2:
            return QString("Source");
        case 3:
            return QString("Destination");
        case 4:
            return QString("DEP");
        case 5:
            return QString("ARR");
        case 6:
            return QString("Status");
        }
    }
    return QVariant();
}

void FlightTableModel::recordRemovedSlot(int index)
{
    this->removeRows(index, 1);
    emit recordRemovedSignal(index);
}


