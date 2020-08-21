#ifndef FLIGHTTABLEMODEL_H
#define FLIGHTTABLEMODEL_H

//#include "mymodel.h"
//class Flight;
//#include "Recorder.h"
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
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    static FlightTableModel* getInstance();

private:
    static FlightTableModel* instance;

    //QTimer * timer;

    //Recorder<Flight> * recorder;

signals:
    void recordInsertedSignal(int);
//    void recordInsertedSignal();
    void recordRemovedSignal(int);

public slots:
    void timerHit();
private slots:
    void recordInserted();
    void recordRemovedSlot(int);
    //void recordInserted() override;
};

#endif // FLIGHTTABLEMODEL_H
