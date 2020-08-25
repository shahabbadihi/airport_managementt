#ifndef PILOTLISTMODEL_H
#define PILOTLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

class PilotListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    PilotListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static PilotListModel* getInstance();

private:
    static PilotListModel* instance;

private slots:
signals:
    void rowsAboutToBeRemoved(int);

};

#endif // PILOTLISTMODEL_H
