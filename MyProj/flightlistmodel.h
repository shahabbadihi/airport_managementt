#ifndef FLIGHTLISTMODEL_H
#define FLIGHTLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

class FlightListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    FlightListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static FlightListModel* getInstance();

private:
    static FlightListModel* instance;

private slots:
signals:
    void rowsAboutToBeRemoved(int);

};

#endif // FLIGHTLISTMODEL_H
