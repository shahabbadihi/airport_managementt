#ifndef FLIGHTTABLEMODEL_H
#define FLIGHTTABLEMODEL_H

#include "mymodel.h"

class FlightTableModel : public MyModel
{
public:
    FlightTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
//    QModelIndex parent(const QModelIndex &index) const override;
//    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
//    bool insertRows(int row, int count, const QModelIndex &parent) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static FlightTableModel* getInstance();

private:
    static FlightTableModel* instance;

private slots:
    void timerHit() override;
    //void recordInserted() override;
};

#endif // FLIGHTTABLEMODEL_H
