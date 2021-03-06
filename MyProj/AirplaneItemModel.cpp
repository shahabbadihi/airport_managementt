#include "AirplaneItemModel.h"
#include "Recorder.h"
#include "Airplane.h"
#include "Airline.h"
#include "Flight.h"

AirplaneItemModel* AirplaneItemModel::instance;

AirplaneItemModel::AirplaneItemModel(QObject *parent)
    : MyAbstractItemModel(parent)
{
    connect(this, SIGNAL(rowsAboutToBeRemoved(int)),
            Recorder<Airplane>::getInstance(), SLOT(recordRemovedSlot(int)));

    connect(Recorder<Airplane>::getInstance(), SIGNAL(recordRemovedSignal(int)),
            this, SLOT(rowRemovedSlot(int)));

    connect(Recorder<Airplane>::getInstance(), SIGNAL(recordAdded()),
            this, SLOT(rowAddedSlot()));
}

int AirplaneItemModel::rowCount(const QModelIndex &/*parent*/) const
{
    return Recorder<Airplane>::getInstance()->get_dataList().size();
}

bool AirplaneItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    connect(this, SIGNAL(rowsAboutToBeRemoved(int)),
            Recorder<Airplane>::getInstance(), SLOT(recordRemovedSlot(int)));

    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    emit rowsAboutToBeRemoved(row);
    return true;
}

QModelIndex AirplaneItemModel::parent(const QModelIndex &/*index*/) const
{
    return QModelIndex();
}

QModelIndex AirplaneItemModel::index(int row, int column, const QModelIndex &/*parent*/) const
{
    return createIndex(row, column);
}

int AirplaneItemModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 5;
}

QVariant AirplaneItemModel::data(const QModelIndex &index, int role) const
{
    Airplane * p = Recorder<Airplane>::getInstance()->get_dataList()[index.row()];
    QString s = "";
    foreach (Flight* f, p->getFlightList())
    {
        s += f->getFlightStr() + "\n";
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (index.column())
        {
        case 0:
            return p->getSerial();
            break;
        case 1:
            return QString::number(p->getRowCount());
            break;
        case 2:
            return QString::number(p->getcolumnCount());
            break;
        case 3:
            return p->getAirline()->getName();
            break;
        case 4:
            return s;
            break;
        }
    }
    return QVariant();
}

bool AirplaneItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Airplane * p = Recorder<Airplane>::getInstance()->get_dataList()[index.row()];

    if (role == Qt::EditRole)
    {
        switch (index.column())
        {
        case 0:
            p->setSerial(value.toString());
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        }
    }
    return true;
}

AirplaneItemModel *AirplaneItemModel::getInstance()
{
    if (instance == nullptr)
        instance = new AirplaneItemModel(nullptr);
    return instance;
}

void AirplaneItemModel::rowRemovedSlot(int r)
{
    disconnect(this, SIGNAL(rowsAboutToBeRemoved(int)),
            Recorder<Airplane>::getInstance(), SLOT(recordRemovedSlot(int)));

    emit rowsAboutToBeRemoved(r);
}
