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
    this->proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    proxy->setDynamicSortFilter(true);
    ui->listView->setModel(proxy);

    //ui->listView->setRootIndex(proxy->mapFromSource(model->index(model->rootPath())));



    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
            proxy,          SLOT(setFilterFixedString(QString)));
//    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
//            model, SLOT(updateFilter(QString)));

}

deleteTicket::~deleteTicket()
{
    delete ui;
}

//void deleteTicket::on_lineEdit_textChanged(const QString &arg1)
//{
   // model->match(model->index(0, 0), Qt::DisplayRole, QVariant::fromValue(ui->lineEdit), -1, Qt::MatchStartsWith);
//    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
//    proxy->setSourceModel(model);
//    ui->listView->setModel(proxy);
//            connect(ui->lineEdit, SIGNAL(textChanged(&arg1)),
//                         proxy, SLOT(setFilterFixedString(&arg1)));
//    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
//            model, SLOT(updateFilter(QString)));
//    model->updateFilter(arg1);
//    ui->listView->setModel(model);
//}

void deleteTicket::on_deleteButton_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    this->proxy->removeRows(index.row(), 1);

    //this->model->removeRows(index.row(), 1);
   //
   //
   QMessageBox msg;
   msg.setText("Delete Successfully!");
   msg.exec();

//}
//}
}

//void deleteTicket::on_serachButton_clicked()
//{

//}

void deleteTicket::on_cancelButton_clicked()
{
    this->close();
}
