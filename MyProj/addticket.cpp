#include "addticket.h"
#include "ui_addticket.h"
#include "Ticket.h"
#include "Recorder.h"
#include "Flight.h"
#include "Passenger.h"
#include <QMessageBox>

template <class T>
Recorder<T>* Recorder<T>::instance;

AddTicket::AddTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTicket)
{
    ui->setupUi(this);
}

AddTicket::~AddTicket()
{
    delete ui;
}

void AddTicket::on_btnSubmit_clicked()
{
    Ticket* ticket = nullptr;
    foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
    {
        if (f->getSource() == ui->txtSource->text() &&
                f->getDestination() == ui->txtDest->text() &&
                f->getDateTimeDeparture().date() == ui->dtDate->date() &&
                f->getNumOfPassengers() > 0)
        {
            ticket = new Ticket();
            ticket->setNo(ui->txtNo->text().toLong());
            //ticket->setSource(ui->txtSource->text());
            //ticket->setDestination(ui->txtDest->text());

            Passenger* passenger = new Passenger;
            passenger->setNationalCode(ui->txtNationalCode->text().toLong());
            passenger->setFname(ui->txtFName->text());
            passenger->setLname(ui->txtLName->text());
            passenger->setBirthDate(ui->dtBirthDate->date());
            passenger->setFatherName(ui->txtPassFatherName->text());

            passenger->setTicket(ticket);

            Recorder<Passenger>::getInstance()->add(passenger);

            ticket->setPassenger(passenger);
            //ticket->setDateFlight(ui->dtDate->date());
            ticket->setFlight(f);
            //ticket->setTimeFlight(ticket->getFlight()->getDateTimeDeparture().time());
            //ticket->setDateTimeArrival(ticket->getFlight()->getDateTimeArrival());

            Recorder<Ticket>::getInstance()->add(ticket);

            break;
        }
    }

    if (!ticket)
    {
        QMessageBox msg;
        msg.setText("There Is No Flight For This Date");
        msg.exec();
        return;
    }
    else
    {
        QMessageBox msg;
        msg.setText("Submit Successfully!\nThe Flight Serial Is: " + ticket->getFlight()->getSerial()
                    + "\nDeparture Time: " + ticket->getFlight()->getDateTimeDeparture().time().toString());
        msg.exec();
    }


}

void AddTicket::on_btnCancel_clicked()
{
    this->close();
}