#include "HostItemModel.h"
#include "Recorder.h"
#include "Host.h"
#include "Flight.h"
#include "Airline.h"

HostItemModel* HostItemModel::instance;

HostItemModel::HostItemModel(QObject *parent)
    : MyAbstractItemModel(parent)
{

    connect(Recorder<Host>::getInstance(), SIGNAL(recordRemovedSignal(int)),
            this, SLOT(rowRemovedSlot(int)));

    connect(Recorder<Host>::getInstance(), SIGNAL(recordAdded()),
            this, SLOT(rowAddedSlot()));
}

int HostItemModel::rowCount(const QModelIndex &/*parent*/) const
{
    return Recorder<Host>::getInstance()->get_dataList().size();
}

bool HostItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    emit rowsAboutToBeRemoved(row);
    return true;
}

QModelIndex HostItemModel::parent(const QModelIndex &/*index*/) const
{
    return QModelIndex();
}

QModelIndex HostItemModel::index(int row, int column, const QModelIndex &/*parent*/) const
{
    return createIndex(row, column);
}

int HostItemModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 10;
}

QVariant HostItemModel::data(const QModelIndex &index, int /*role*/) const
{
    Host * p = Recorder<Host>::getInstance()->get_dataList()[index.row()];
    QString s = "";
    foreach (Flight* f, p->getFlightList())
    {
        s += f->getFlightStr() + "\n";
    }

    QString s2 = "";
    foreach (Flight* f, p->getDoneFlightList())
    {
        s2 += f->getFlightStr() + "\n";
    }

    QString s3 = QString::number(p->wage());


    switch (index.column())
    {
    case 0:
        return p->getFname();
        break;
    case 1:
        return p->getLname();
        break;
    case 2:
        return QString::number(p->getNationalCode());
        break;
    case 3:
        return QString::number(p->getPersonnelCode());
        break;
    case 4:
        return p->getAirline()->getName();
        break;
    case 5:
        return p->getBirthDate();
        break;
    case 6:
        return p->getEmploymentDate();
        break;
    case 7:
        return s;
        break;
    case 8:
        return s2;
        break;
    case 9:
        return s3;
        break;
    }
    return QVariant();
}

bool HostItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Host * p = Recorder<Host>::getInstance()->get_dataList()[index.row()];

    if (role == Qt::EditRole)
    {
        switch (index.column())
        {
        case 0:
            p->set_fname(value.toString());
            break;
        case 1:
            p->set_lname(value.toString());
            break;
        case 2:
            p->set_nationalCode(value.toLongLong());
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        }
    }
    return true;
}

HostItemModel *HostItemModel::getInstance()
{
    if (instance == nullptr)
        instance = new HostItemModel(nullptr);
    return instance;
}

void HostItemModel::rowRemovedSlot(int r)
{
    this->removeRows(r, 1);
}
