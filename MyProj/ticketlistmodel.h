#ifndef TICKETLISTMODEL_H
#define TICKETLISTMODEL_H

#include <QAbstractListModel>

class TicketListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TicketListModel(QObject *parent = nullptr);

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
public:
   static TicketListModel* getInstance();
signals:
    void rowsAboutToBeRemoved(int);

private:
    static TicketListModel* instance;
};

#endif // TICKETLISTMODEL_H
