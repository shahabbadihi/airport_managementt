#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QTimer>

class MyModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    MyModel();
    MyModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static MyModel* getInstance();
private:
    static MyModel* instance;
    QTimer * timer;

private slots:
    void timerHit();
    //void recordInserted();
};

#endif // MYMODEL_H
