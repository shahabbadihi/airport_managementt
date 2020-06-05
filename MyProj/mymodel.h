#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QTimer>


class MyModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    MyModel(QObject *parent = nullptr);
//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
//    QModelIndex parent(const QModelIndex &index) const override;
//    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
//    bool insertRows(int row, int count, const QModelIndex &parent) override;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//    static MyModel* getInstance();
protected:
//    static MyModel* instance;
    QTimer * timer;

private slots:
    virtual void timerHit() = 0;
    virtual void recordInserted() = 0;
};

#endif // MYMODEL_H
