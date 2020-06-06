#include "pilotlistmodel.h"
#include "Recorder.h"
#include "Pilot.h"

template <class T>
Recorder<T>* Recorder<T>::instance;

PilotListModel* PilotListModel::instance;

PilotListModel::PilotListModel(QObject *parent)
    : MyModel(parent)
{

}

int PilotListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return Recorder<Pilot>::getInstance()->get_dataList().size();
}

int PilotListModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 0;
}

PilotListModel* PilotListModel::getInstance()
{
    if (instance == nullptr)
        instance = new PilotListModel(nullptr);
    return instance;
}

void PilotListModel::timerHit()
{

}

QVariant PilotListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return Recorder<Pilot>::getInstance()->get_dataList()[index.row()]->getFname() + " " +
                Recorder<Pilot>::getInstance()->get_dataList()[index.row()]->getLname() + " " +
                Recorder<Pilot>::getInstance()->get_dataList()[index.row()]->getPersonnelCode();
    }
    return QVariant();
}
