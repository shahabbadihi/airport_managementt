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




    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
            proxy,          SLOT(setFilterFixedString(QString)));

}

deleteTicket::~deleteTicket()
{
    delete ui;
}

void deleteTicket::on_deleteButton_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    this->proxy->removeRows(index.row(), 1);


    QMessageBox msg;
    msg.setText("Delete Successfully!");
    msg.exec();
}


void deleteTicket::on_cancelButton_clicked()
{
    this->close();
}
