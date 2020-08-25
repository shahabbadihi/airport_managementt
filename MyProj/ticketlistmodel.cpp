#include "ticketlistmodel.h"
#include "Recorder.h"
#include "Ticket.h"
#include "Flight.h"

TicketListModel* TicketListModel::instance;
TicketListModel::TicketListModel(QObject *parent)
    : QAbstractListModel(parent)
{
       connect(this, SIGNAL(rowsAboutToBeRemoved(int)), Recorder<Ticket>::getInstance(), SLOT(recordRemovedSlot(int)));
}

int TicketListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return Recorder<Ticket>::getInstance()->get_dataList().size();
}

QVariant TicketListModel::data(const QModelIndex &index, int role) const
{

    if (role == Qt::DisplayRole)
    {
        return QString::number(index.row())+" | " +
                QString::number(Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getNo())+ " | " +
                Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getPassengerName()+" | "+
                Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getFlight()->getSerial()+" | "+
                Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getFlight()->getSource()+" | "+
                Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getFlight()->getDestination()+" | "+
                QString::number(Recorder<Ticket>::getInstance()->get_dataList()[index.row()]->getPassenger()->getNationalCode())+" | ";
    }

    return QVariant();
}

TicketListModel* TicketListModel::getInstance()
{
    if (instance == nullptr)
        instance = new TicketListModel(nullptr);
    return instance;
}

bool TicketListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    emit rowsAboutToBeRemoved(row);
    return true;
}
