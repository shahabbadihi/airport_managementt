#ifndef PILOTTABLEMODEL_H
#define PILOTTABLEMODEL_H

#include "MyAbstractItemModel.h"
#include <QObject>

class PilotItemModel : public MyAbstractItemModel
{
    Q_OBJECT
public:
    PilotItemModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    static PilotItemModel *getInstance();

private:
    static PilotItemModel* instance;

public slots:

private slots:
    void rowRemovedSlot(int) override;
};

#endif // PILOTLISTMODEL_H
