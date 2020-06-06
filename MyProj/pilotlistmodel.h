#ifndef PILOTLISTMODEL_H
#define PILOTLISTMODEL_H

#include "mymodel.h"

class PilotListModel : public MyModel
{
public:
    PilotListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static PilotListModel* getInstance();

private:
    static PilotListModel* instance;

private slots:
    virtual void timerHit() override;
    //virtual void recordInserted();

};

#endif // PILOTLISTMODEL_H
