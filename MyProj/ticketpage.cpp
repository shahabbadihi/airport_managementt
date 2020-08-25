#include "ticketpage.h"
#include "ui_ticketpage.h"
#include "Flight.h"
#include "Airline.h"
#include "addticket.h"
TicketPage::TicketPage(Ticket * t,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TicketPage)
{
    ticket = t ;
    ui->setupUi(this);
    update();
    this->model = TicketListModel::getInstance();
    this->proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    proxy->setDynamicSortFilter(true);
    ui->listView->setModel(proxy);
    proxy->setFilterFixedString(QString::number(ticket->getPassenger()->getNationalCode()));
}

TicketPage::~TicketPage()
{
    delete ui;
}

void TicketPage::update(){
    ui->NameLe->setText(this->ticket->getPassengerName());
    ui->TicketNoLe->setText(QString::number(ticket->getNo()));
    ui->FlightNoLe->setText(ticket->getFlight()->getSerial());
    ui->SourceLe->setText(ticket->getFlight()->getSource());
    ui->DestinationLe->setText(ticket->getFlight()->getDestination());
    ui->AirlineLe->setText(ticket->getFlight()->getAirline()->getName());
    ui->DateTimeLe->setText(ticket->getFlight()->getDateTimeDeparture().toString());
    ui->DateTimeLe_2->setText(ticket->getFlight()->getDateTimeArrival().toString());
    ui->PriceLe->setText(QString::number(ticket->getPrice()));
    ui->FatherNameLe->setText(ticket->getPassenger()->getFatherName());
    ui->dateEdit->setDate(ticket->getPassenger()->getBirthDate());
    ui->dateEdit->setReadOnly(true);
    ui->NationalCodeLe->setText(QString::number(ticket->getPassenger()->getNationalCode()));
    ui->NationalCodeLe->setReadOnly(true);
}

void TicketPage::on_listView_doubleClicked(const QModelIndex &index)
{
    QStringList str = index.data().toString().split(" | ");
    this->ticket=Recorder<Ticket>::getInstance()->searchByCode(str[1]);
    update();
}

void TicketPage::on_pushButton_clicked()
{
    if(Recorder<Ticket>::getInstance()->searchByCode(ui->TicketNoLe->text())==nullptr){
        ticket->setNo(ui->TicketNoLe->text().toLong());
    }
    else{
        QMessageBox msg;
        msg.setText("the ticket No already used.");
        msg.exec();
        return;
    }

    QStringList str=ui->NameLe->text().split(" ");

    if (str.size() == 1)
    {
        QMessageBox msg;
        msg.setText("Please Enter Full Name!");
        msg.exec();
        return;
    }

    ticket->getPassenger()->setFname(str[0]);
    ticket->getPassenger()->setLname(str[1]);
    ticket->getPassenger()->setFatherName(ui->FatherNameLe->text());
    update();
    this->close();
}

void TicketPage::on_pushButton_2_clicked()
{
    AddTicket *a=new AddTicket(ticket->getPassenger());
    a->exec();
}
