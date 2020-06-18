#ifndef TEXTBOXDELEGATE_H
#define TEXTBOXDELEGATE_H
#include <QObject>
#include <QItemDelegate>

class Delegate : public QItemDelegate
{
    Q_OBJECT

public:
    Delegate(QObject *parent = 0);
    //void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    //    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
};

#endif // TEXTBOXDELEGATE_H
