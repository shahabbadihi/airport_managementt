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

    //int rootPath();
public slots:
   //void updateFilter(QString filter);
public:
   static TicketListModel* getInstance();
signals:
    void rowsAboutToBeRemoved(const QString&);

private:
    static TicketListModel* instance;
    //QString _fliter;
};

#endif // TICKETLISTMODEL_H
