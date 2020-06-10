#include "deleteticket.h"
#include "ui_deleteticket.h"

deleteTicket::deleteTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteTicket)
{
    ui->setupUi(this);
}

deleteTicket::~deleteTicket()
{
    delete ui;
}
