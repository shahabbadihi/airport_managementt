#ifndef AIRLINEITEMMODEL_H
#define AIRLINEITEMMODEL_H

#include <QAbstractItemModel>

class AirlineItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit AirlineItemModel(QObject *parent = nullptr);
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;



    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    static AirlineItemModel *getInstance();

private:
    static AirlineItemModel* instance;
};

#endif // AIRLINEITEMMODEL_H
