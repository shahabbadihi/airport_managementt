#include "ticketlistmodel.h"
#include "Recorder.h"
#include "Ticket.h"
template <class T>
Recorder<T>* Recorder<T>::instance;

TicketListModel* TicketListModel::instance;
TicketListModel::TicketListModel(QObject *parent)
    : QAbstractListModel(parent)
{
       connect(this, SIGNAL(rowsAboutToBeRemoved(const QString&)), Recorder<Ticket>::getInstance(), SLOT(recordRemovedSlot(const QString&)));
}

int TicketListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return Recorder<Ticket>::getInstance()->get_dataList().size();
}

QVariant TicketListModel::data(const QModelIndex &index, int role) const
{

    if (role == Qt::DisplayRole /*&&!_fliter.isEmpty() &&
            QString::number(Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getNo())
            .toLower().contains(_fliter.toLower())*/)
    {
        return QString::number(Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getNo())+ " " +
                Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getPassengerName();
    }
//    else if (role == Qt::DisplayRole)
//    {
//        return QString::number(Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getNo())+ " " +
//                Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getPassengerName();
//    }

    return QVariant();
}


//int TicketListModel::rootPath()
//{
//    return 0;
//}

TicketListModel* TicketListModel::getInstance()
{
    if (instance == nullptr)
        instance = new TicketListModel(nullptr);
    return instance;
}
//void TicketListModel::updateFilter(QString filter){
//    this->_fliter = filter;
//    emit layoutChanged();
//}
bool TicketListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    QModelIndex index = createIndex(row, 0);
    QString search_code = this->data(index).toString().split(" ")[0];
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    emit rowsAboutToBeRemoved(search_code);
    return true;
}
