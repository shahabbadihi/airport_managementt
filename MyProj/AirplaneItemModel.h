#ifndef AIRPLANEITEMMODEL_H
#define AIRPLANEITEMMODEL_H

#include <QObject>
#include "MyAbstractItemModel.h"

class AirplaneItemModel : public MyAbstractItemModel
{
    Q_OBJECT
public:
    AirplaneItemModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    static AirplaneItemModel *getInstance();

private:
    static AirplaneItemModel* instance;

private slots:
    void rowRemovedSlot(int) override;
};

#endif // AIRPLANEITEMMODEL_H
