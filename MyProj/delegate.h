#ifndef TEXTBOXDELEGATE_H
#define TEXTBOXDELEGATE_H
#include <QObject>
#include <QItemDelegate>

class Delegate : public QItemDelegate
{
    Q_OBJECT

public:
    Delegate(QObject *parent = 0);
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
};

#endif // TEXTBOXDELEGATE_H
