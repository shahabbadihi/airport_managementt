#ifndef FLIGHTTABLEMODEL_H
#define FLIGHTTABLEMODEL_H

//#include "mymodel.h"
#include <QAbstractItemModel>
#include <QObject>
#include <QTimer>

class FlightTableModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    FlightTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//    QModelIndex parent(const QModelIndex &index) const override;
//    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
//    bool insertRows(int row, int count, const QModelIndex &parent) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static FlightTableModel* getInstance();

private:
    static FlightTableModel* instance;

    QTimer * timer;

private slots:
    void timerHit();
    void recordInserted();
    void recordRemovedSlot(int);
    //void recordInserted() override;
};

#endif // FLIGHTTABLEMODEL_H
