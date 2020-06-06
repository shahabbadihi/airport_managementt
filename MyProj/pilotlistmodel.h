#ifndef PILOTLISTMODEL_H
#define PILOTLISTMODEL_H

//#include "mymodel.h"
#include <QAbstractListModel>
#include <QObject>

class PilotListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    PilotListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    QModelIndex parent(const QModelIndex &index) const override;
//    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
   // bool insertRows(int row, int count, const QModelIndex &parent) override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static PilotListModel* getInstance();

private:
    static PilotListModel* instance;

private slots:
//    void timerHit();
    //virtual void recordInserted();

};

#endif // PILOTLISTMODEL_H
