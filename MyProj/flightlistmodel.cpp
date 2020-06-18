#include "flightlistmodel.h"
#include "Recorder.h"
#include "Flight.h"

FlightListModel* FlightListModel::instance;

FlightListModel::FlightListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(this, SIGNAL(rowsAboutToBeRemoved(int)), Recorder<Flight>::getInstance(), SLOT(recordRemovedSlot(int)));
}

int FlightListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return Recorder<Flight>::getInstance()->get_dataList().size();
}

bool FlightListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    emit rowsAboutToBeRemoved(row);
    return true;
}

FlightListModel* FlightListModel::getInstance()
{
    if (instance == nullptr)
        instance = new FlightListModel(nullptr);
    return instance;
}

QVariant FlightListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return Recorder<Flight>::getInstance()->get_dataList()[index.row()]->getFlightStr();
    }
    return QVariant();
}
