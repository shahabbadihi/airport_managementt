#include "deleteticket.h"
#include "ui_deleteticket.h"
#include <QSortFilterProxyModel>
#include <QMessageBox>
deleteTicket::deleteTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteTicket)
{
    ui->setupUi(this);
    this->model = TicketListModel::getInstance();
    ui->listView->setModel(model);
    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
            model, SLOT(updateFilter(QString)));

}

deleteTicket::~deleteTicket()
{
    delete ui;
}

void deleteTicket::on_lineEdit_textChanged(const QString &arg1)
{
   // model->match(model->index(0, 0), Qt::DisplayRole, QVariant::fromValue(ui->lineEdit), -1, Qt::MatchStartsWith);
//    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
//    proxy->setSourceModel(model);
//    ui->listView->setModel(proxy);
//            connect(ui->lineEdit, SIGNAL(textChanged(&arg1)),
//                         proxy, SLOT(setFilterFixedString(&arg1)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
            model, SLOT(updateFilter(QString)));
    model->updateFilter(arg1);
    ui->listView->setModel(model);
}

void deleteTicket::on_deleteButton_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    this->model->removeRows(index.row(), 1);
   //
   //
   QMessageBox msg;
   msg.setText("Delete Successfully!");
   msg.exec();

//}
//}
}
