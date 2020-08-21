#include "addticket.h"
#include "ui_addticket.h"
#include "Ticket.h"
#include "Recorder.h"
#include "Flight.h"
#include "Passenger.h"
#include "p2_12.h"
#include "pu2.h"
#include "po12.h"
#include "GetPassengerFactory.h"
#include <QMessageBox>
#include <stdexcept>
#include <QDateTime>
using namespace std;

AddTicket::AddTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTicket)
{
    ui->setupUi(this);
}

AddTicket::AddTicket(Passenger *p,QWidget *parent ):
    QDialog(parent),
    ui(new Ui::AddTicket)
{
    ui->setupUi(this);
    ui->txtFName->setText(p->getFname());
    ui->txtFName->setReadOnly(true);
    ui->txtLName->setText(p->getLname());
    ui->txtLName->setReadOnly(true);
    ui->txtNationalCode->setText(QString::number(p->getNationalCode()));
    ui->txtNationalCode->setReadOnly(true);
    ui->txtPassFatherName->setText(p->getFatherName());
    ui->txtPassFatherName->setReadOnly(true);
    ui->dtBirthDate->setDate(p->getBirthDate());
    ui->dtBirthDate->setReadOnly(true);
}

AddTicket::~AddTicket()
{
    delete ui;
}

void AddTicket::on_btnSubmit_clicked()
{
    long no = ui->txtNo->text().toLong();
    qlonglong national_code = ui->txtNationalCode->text().toLongLong();
    QString fname = ui->txtFName->text();
    QString lname = ui->txtLName->text();
    QDate b_date = ui->dtBirthDate->date();
    QString father_name = ui->txtPassFatherName->text();

    Ticket* ticket = nullptr;

    try
    {
        ticket = new Ticket(no, b_date, ui->dtDate->date(), national_code,
                                    fname, lname, father_name);

        Recorder<Ticket>::getInstance()->add(ticket);

        foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
        {
            if (f->isSuitable(ticket->getPassenger(), ui->txtSource->text(),
                              ui->txtDest->text(), ui->dtDate->date()))
            {
                QDateTime departure = f->getDateTimeDeparture();
                QDateTime destination = f->getDateTimeArrival();
                double seconds = departure.secsTo(destination);
                double price = (seconds * 5) / 72;
                qDebug() << price;
                ticket->setFlight(f);
                ticket->setPrice(price);

                break;
            }
        }


        if (!ticket->getFlight())
        {
            Recorder<Ticket>::getInstance()->remove(ticket);
            QMessageBox msg;
            msg.setText("There Is No Flight For This Date");
            msg.exec();
            return;
        }
        else
        {

            QMessageBox msg;
            msg.setText("Submit Successfully!\nThe Flight Serial Is: " + ticket->getFlight()->getSerial()
                        + "\nDeparture Time: " + ticket->getFlight()->getDateTimeDeparture().time().toString()
                        + "\n\nTicket Price Is " + QString::number(ticket->getPrice()));
            msg.exec();

            if (ticket->getFlight()->isPassengerEnough())
            {
                QString s3 = "Flight ";
                QString s4 = " Now Has Enough Tickets!";
                QMessageBox msg;
                msg.setText(s3 + ticket->getFlight()->getSerial() + s4);
                msg.show();
            }
        }
    }
    catch (invalid_argument e)
    {
        delete ticket;
        ticket = nullptr;
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }


}

void AddTicket::on_btnCancel_clicked()
{
    this->close();
}
