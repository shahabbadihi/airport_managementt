#include "attachticket.h"
#include "ui_attachticket.h"
#include "Recorder.h"
#include "Ticket.h"
#include <stdexcept>
using namespace std;
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
    try
    {
        Ticket * t = Recorder<Ticket>::getInstance()->searchByCode(ui->lineEdit->text());

        if (!flight->isTicketInList(t))
        {
            throw invalid_argument("This Flight Has Not This Ticket!");
        }

        if(flight->getAirplane()->getSeat(Row,Column)->isFree(flight)){
            flight->getAirplane()->getSeat(Row,Column)->attachTicket(t);
        }
        else{
            flight->getAirplane()->getSeat(Row,Column)->removeTicket(flight->getAirplane()->getSeat(Row,Column)->getTicket(flight));
            flight->getAirplane()->getSeat(Row,Column)->attachTicket
                    (t);
        }

        ui->name->setText(t->getPassengerName());
    }
    catch (invalid_argument e)
    {
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }
}

void attachTicket::on_editButton_clicked()
{
   Recorder<Ticket>::getInstance()->searchByCode(ui->lineEdit->text())->setSeat(flight->getAirplane()->getSeat(Row,Column));
   this->close();
}
