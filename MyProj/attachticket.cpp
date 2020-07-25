#include "attachticket.h"
#include "ui_attachticket.h"
#include "Recorder.h"
#include "Ticket.h"
attachTicket:: attachTicket(Flight *flight ,int row ,int col,QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::attachTicket)
{
    this->flight=flight;
    Row=row;
    Column=col;
    ui->setupUi(this);
}

attachTicket::~attachTicket()
{
    delete ui;
}

void attachTicket::on_okButton_clicked()
{
    flight->getAirplane()->getSeat(Row,Column)->attachTicket
            ( Recorder<Ticket>::getInstance()->searchByCode(ui->lineEdit->text()));
    ui->name->setText(Recorder<Ticket>::getInstance()->searchByCode(ui->lineEdit->text())->getPassengerName());
}
