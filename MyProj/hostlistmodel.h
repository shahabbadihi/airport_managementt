#ifndef HOSTLISTMODEL_H
#define HOSTLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

class HostListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    HostListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static HostListModel* getInstance();

private:
    static HostListModel* instance;

private slots:
signals:
    void rowsAboutToBeRemoved(int);

};

#endif // HOSTLISTMODEL_H
