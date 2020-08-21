#ifndef MYABSTRACTITEMMODEL_H
#define MYABSTRACTITEMMODEL_H

#include <QObject>
#include <QAbstractItemModel>

class MyAbstractItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    MyAbstractItemModel(QObject *parent = nullptr);

private slots:
    virtual void rowRemovedSlot(int) = 0;
    void rowAddedSlot();
signals:
    void rowsAboutToBeRemoved(int);
    void setIndexWhenRecordAdded();
};

#endif // MYABSTRACTITEMMODEL_H
