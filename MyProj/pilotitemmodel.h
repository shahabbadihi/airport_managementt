#ifndef PILOTTABLEMODEL_H
#define PILOTTABLEMODEL_H

//#include "mymodel.h"
#include <QAbstractListModel>
#include <QObject>

class PilotItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    PilotItemModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
   // bool insertRows(int row, int count, const QModelIndex &parent) override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    static PilotItemModel *getInstance();

private:
    static PilotItemModel* instance;

public slots:

private slots:
    void rowRemovedSlot(int);
    void rowAddedSlot();
signals:
    void rowsAboutToBeRemoved(int);
    void setIndexWhenRecordAdded();
};

#endif // PILOTLISTMODEL_H
