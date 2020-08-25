#ifndef HOSTITEMMODEL_H
#define HOSTITEMMODEL_H

#include <QObject>
#include "MyAbstractItemModel.h"

class HostItemModel : public MyAbstractItemModel
{
    Q_OBJECT
public:
    HostItemModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    static HostItemModel *getInstance();

private:
    static HostItemModel* instance;

private slots:
    void rowRemovedSlot(int) override;
};

#endif // HOSTITEMMODEL_H
