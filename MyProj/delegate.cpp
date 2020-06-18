#include "delegate.h"
#include <QtGui>
#include <QApplication>
#include <QLineEdit>
#include "Recorder.h"
#include "Flight.h"

Delegate::Delegate(QObject *parent)
     : QItemDelegate(parent)
{
}

void Delegate::setEditorData(QWidget *editor,
                           const QModelIndex &index) const
    {
      if (!editor->metaObject()->userProperty().isValid()) {
        if (editor->property("currentIndex").isValid()) {
          editor->setProperty("currentIndex", index.data());
          return;
        }
      }
      QItemDelegate::setEditorData(editor, index);
    }

void Delegate::setModelData(QWidget *editor,
                         QAbstractItemModel *model,
                         const QModelIndex &index) const
    {
      if (!editor->metaObject()->userProperty().isValid()) {
        QVariant value = editor->property("currentIndex");
        if (value.isValid()) {
          model->setData(index, value);
          return;
        }
      }
      QItemDelegate::setModelData(editor, model, index);
    }
