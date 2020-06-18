#include "pilotitemmodel.h"
#include "Pilot.h"
#include "Flight.h"
#include "Airline.h"
#include "Recorder.h"
#include <QStringListModel>

PilotItemModel* PilotItemModel::instance;

PilotItemModel::PilotItemModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

int PilotItemModel::rowCount(const QModelIndex &/*parent*/) const
{
    return Recorder<Pilot>::getInstance()->get_dataList().size();
}

bool PilotItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    emit rowsAboutToBeRemoved(row);
    return true;
}

QModelIndex PilotItemModel::parent(const QModelIndex &/*index*/) const
{
    return QModelIndex();
}

QModelIndex PilotItemModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

int PilotItemModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 10;
}

QVariant PilotItemModel::data(const QModelIndex &index, int role) const
{
    Pilot * p = Recorder<Pilot>::getInstance()->get_dataList()[index.row()];
    QString s = "";
    foreach (Flight* f, p->getFlightList())
    {
        s += f->getFlightStr() + "\n";
    }

    QString s2 = "";
    foreach (Flight* f, p->getDoneFlightList())
    {
        s += f->getFlightStr() + "\n";
    }

    //QStringListModel ss;
    //ss.setStringList(s);


//    if (role == Qt::DisplayRole)
//    {
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
        return p->getDegreeAsString();
        break;
    }
    //}
    return QVariant();
}

bool PilotItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Pilot * p = Recorder<Pilot>::getInstance()->get_dataList()[index.row()];

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
            p->set_personnelCode(value.toLongLong());
            break;
        case 4:
            //p->setAirline();
            break;
        case 5:
            p->set_birthDate(value.toDate());
            break;
        case 6:
            p->set_employmentDate(value.toDate());
            break;
        case 7:
            //return s;
            break;
        case 8:
            //p->;
            break;
        case 9:
            break;
        }
    }
}

PilotItemModel *PilotItemModel::getInstance()
{
    if (instance == nullptr)
        instance = new PilotItemModel(nullptr);
    return instance;
}
