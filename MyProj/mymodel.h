#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
//#include <QAbstractItemModel>
#include <QTimer>
#include "SignalSlot.h"


template <class T>
class MyModel : public SignalSlot
{

public:
    MyModel();
    MyModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static MyModel* getInstance();
private:
    static MyModel* instance;
    QTimer * timer;

private slots:
    void timerHit();
    void recordInserted();
};

#endif // MYMODEL_H
