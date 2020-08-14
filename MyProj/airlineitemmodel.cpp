#include "airlineitemmodel.h"
#include "Airline.h"
#include "Pilot.h"
#include "Host.h"
#include "Flight.h"
#include "Airplane.h"
AirlineItemModel* AirlineItemModel::instance;

AirlineItemModel::AirlineItemModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}


QModelIndex AirlineItemModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);

}

QModelIndex AirlineItemModel::parent(const QModelIndex &/*index*/) const
{
    return QModelIndex();

}

int AirlineItemModel::rowCount(const QModelIndex &parent) const
{
       return Recorder<Airline>::getInstance()->get_dataList().size();
}

int AirlineItemModel::columnCount(const QModelIndex &parent) const
{
    return 7;
}


QVariant AirlineItemModel::data(const QModelIndex &index, int role) const
{
    Airline * a=Recorder<Airline>::getInstance()->get_dataList()[index.row()];
    QString s="";
    foreach (Pilot* p, a->getPilotsList())
    {
        s += p->getFname() +" "+p->getLname()+" "+p->getSearchCode()+ "\n";
    }
    QString s2="";
    foreach (Host* h, a->getHostsList())
    {
        s2 += h->getFname() +" "+h->getLname()+" "+h->getSearchCode()+ "\n";
    }
    QString s3="",s7="";
    foreach (Flight* f, a->getFlightsList())
    {
        if(f->getFlightStateAsString()=="DONE")
            {s7 += f->getFlightStr() + "\n\n";}
        else
            { s3 += f->getFlightStr() + "\n\n";}
    }
    QString s4="";
    foreach (Airplane* A, a->getAirplanesList())
    {
        s4 += A->getSearchCode() + "\n";
    }
    switch (index.column()) {
    case(1):
        return a->getName()+" Airline";
        break;
    case(2):
        return a->getCode();
        break;
    case(3):
        return s;
        break;

    case(4):
        return s2;
        break;
    case(5):
        return s3;
        break;
    case(6):
        return s4;
        break;
    case(7):
        return s7;
        break;
    }
}

bool AirlineItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Airline * a=Recorder<Airline>::getInstance()->get_dataList()[index.row()];

    if (role == Qt::EditRole)
    {
        if(index.column()==2){
            a->setCode(value.toString());
        }
    }
}



bool AirlineItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}


AirlineItemModel *AirlineItemModel::getInstance()
{
    if (instance == nullptr)
        instance = new AirlineItemModel(nullptr);
    return instance;
}
