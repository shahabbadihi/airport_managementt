#include "hostlistmodel.h"
#include "Recorder.h"
#include "Host.h"

template <class T>
Recorder<T>* Recorder<T>::instance;

HostListModel* HostListModel::instance;

HostListModel::HostListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(this, SIGNAL(rowsAboutToBeRemoved(int)), Recorder<Host>::getInstance(), SLOT(recordRemoved(int)));
}

int HostListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return Recorder<Host>::getInstance()->get_dataList().size();
}

bool HostListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    emit rowsAboutToBeRemoved(row);
    return true;
}

HostListModel* HostListModel::getInstance()
{
    if (instance == nullptr)
        instance = new HostListModel(nullptr);
    return instance;
}

QVariant HostListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return Recorder<Host>::getInstance()->get_dataList()[index.row()]->getFname() + " " +
                Recorder<Host>::getInstance()->get_dataList()[index.row()]->getLname() + " " +
                QString::number(Recorder<Host>::getInstance()->get_dataList()[index.row()]->getPersonnelCode());
    }
    return QVariant();
}
