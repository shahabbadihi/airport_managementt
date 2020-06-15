#include "mydelegate.h"
#include <QtGui>
#include <QApplication>
#include "delaydialog.h"
#include "Recorder.h"
#include "Flight.h"

template <class T>
Recorder<T>* Recorder<T>::instance;

MyDelegate::MyDelegate(QObject *parent)
     : QItemDelegate(parent)
{
}

void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    Recorder<Flight>::getInstance()->get_dataList()[index.row()]->delay(60 * 60 * 1000);
}


 void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {
     QStyleOptionButton button;
     QRect r = option.rect;//getting the rect of the cell
     int x,y,w,h;
     x = r.left() + r.width() - 30;//the X coordinate
     y = r.top();//the Y coordinate
     w = 30;//button width
     h = 30;//button height
     button.rect = QRect(x,y,w,h);
     button.text = "Delay";
     button.state = QStyle::State_Enabled;

     QApplication::style()->drawControl( QStyle::CE_PushButton, &button, painter);
 }

 bool MyDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
 {
     if( event->type() == QEvent::MouseButtonRelease )
     {
         QMouseEvent * e = (QMouseEvent *)event;
         int clickX = e->x();
         int clickY = e->y();

         QRect r = option.rect;//getting the rect of the cell
         int x,y,w,h;
         x = r.left() + r.width() - 30;//the X coordinate
         y = r.top();//the Y coordinate
         w = 30;//button width
         h = 30;//button height

         if( clickX > x && clickX < x + w )
             if( clickY > y && clickY < y + h )
             {
//                 DelayDialog * d = new DelayDialog();
//                 int res;
//                 d->setWindowTitle("Set Delay");
//                 d->setGeometry(0,0,100,100);
//                 res = d->exec();

//                 if (res == QDialog::Rejected)
//                 {
//                     return false;
//                 }
//                 if (res == QDialog::Accepted)
//                 {
//                 Recorder<Flight>::getInstance()->get_dataList()[index.row()]->delay(60 * 60 * 1000);
                 //this->setModelData()
                 //}

                 //d->show();
             }
     }

     return true;
 }
