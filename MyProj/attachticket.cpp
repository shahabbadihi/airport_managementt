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
    if(flight->getAirplane()->getSeat(Row,Column)->isFree(flight)){
    flight->getAirplane()->getSeat(Row,Column)->attachTicket
            ( Recorder<Ticket>::getInstance()->searchByCode(ui->lineEdit->text()));
    }
    else{
        flight->getAirplane()->getSeat(Row,Column)->removeTicket(flight->getAirplane()->getSeat(Row,Column)->getTicket(flight));
        flight->getAirplane()->getSeat(Row,Column)->attachTicket
                ( Recorder<Ticket>::getInstance()->searchByCode(ui->lineEdit->text()));
    }

    ui->name->setText(Recorder<Ticket>::getInstance()->searchByCode(ui->lineEdit->text())->getPassengerName());

}

void attachTicket::on_editButton_clicked()
{
   Recorder<Ticket>::getInstance()->searchByCode(ui->lineEdit->text())->setSeat(flight->getAirplane()->getSeat(Row,Column));
   this->close();
}
