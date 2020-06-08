#ifndef FLIGHTLISTMODEL_H
#define FLIGHTLISTMODEL_H

//#include "mymodel.h"
#include <QAbstractListModel>
#include <QObject>

class FlightListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    FlightListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//    QModelIndex parent(const QModelIndex &index) const override;
//    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
   // bool insertRows(int row, int count, const QModelIndex &parent) override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static FlightListModel* getInstance();

private:
    static FlightListModel* instance;

private slots:
//    void timerHit();
    //virtual void recordInserted();
signals:
    void rowsAboutToBeRemoved(int);

};

#endif // FLIGHTLISTMODEL_H
