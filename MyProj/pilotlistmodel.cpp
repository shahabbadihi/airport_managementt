#include "pilotlistmodel.h"
#include "Recorder.h"
#include "Pilot.h"

PilotListModel* PilotListModel::instance;

PilotListModel::PilotListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(this, SIGNAL(rowsAboutToBeRemoved(int)),
            Recorder<Pilot>::getInstance(), SLOT(recordRemovedSlot(int)));
}

int PilotListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return Recorder<Pilot>::getInstance()->get_dataList().size();
}

bool PilotListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    emit rowsAboutToBeRemoved(row);
    return true;
}

PilotListModel* PilotListModel::getInstance()
{
    if (instance == nullptr)
        instance = new PilotListModel(nullptr);
    return instance;
}

QVariant PilotListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return Recorder<Pilot>::getInstance()->get_dataList()[index.row()]->getFname() + " " +
                Recorder<Pilot>::getInstance()->get_dataList()[index.row()]->getLname() + " " +
                QString::number(Recorder<Pilot>::getInstance()->get_dataList()[index.row()]->getPersonnelCode());
    }
    return QVariant();
}
