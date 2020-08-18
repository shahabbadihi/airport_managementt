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

AddTicket::~AddTicket()
{
    delete ui;
}

void AddTicket::on_btnSubmit_clicked()
{
    Ticket* ticket = nullptr;
    try
    {
        foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
        {
            if (f->getSource() == ui->txtSource->text() &&
                    f->getDestination() == ui->txtDest->text() &&
                    f->getDateTimeDeparture().date() == ui->dtDate->date() &&
                    f->getNumOfPassengers() < f->getCapacity())
            {
//                ticket = new Ticket();
//                ticket->setNo(ui->txtNo->text().toLong());
                //ticket->setSource(ui->txtSource->text());
                //ticket->setDestination(ui->txtDest->text());

//                Passenger* passenger = nullptr;

                long no = ui->txtNo->text().toLong();
                qlonglong national_code = ui->txtNationalCode->text().toLongLong();
                QString fname = ui->txtFName->text();
                QString lname = ui->txtLName->text();
                QDate b_date = ui->dtBirthDate->date();
                QString father_name = ui->txtPassFatherName->text();

                QDateTime departure = f->getDateTimeDeparture();
                QDateTime destination = f->getDateTimeArrival();
                double seconds = departure.secsTo(destination);
                double price = (seconds * 5) / 72;
                qDebug() << price;

                ticket = new Ticket(no, b_date, ui->dtDate->date(),
                                    national_code, fname, lname,
                                    father_name, price, f);
//                passenger = GetPassengerFactory::getInstance()->getPassenger(ui->dtBirthDate->date(),
//                                                                                 ui->dtDate->date(),
//                                                                             national_code, fname, lname,
//                                                                             b_date, father_name
//                                                                                 );


//                passenger->setNationalCode(ui->txtNationalCode->text().toLong());
//                passenger->setFname(ui->txtFName->text());
//                passenger->setLname(ui->txtLName->text());
//                passenger->setBirthDate(ui->dtBirthDate->date());
//                passenger->setFatherName(ui->txtPassFatherName->text());

//                passenger->attachTicket(ticket);

//                Recorder<Passenger>::getInstance()->add(passenger);

//                ticket->setPassenger(passenger);
                //ticket->setDateFlight(ui->dtDate->date());

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
                        + "\nDeparture Time: " + ticket->getFlight()->getDateTimeDeparture().time().toString()
                        + "\n\nTicket Price Is " + QString::number(ticket->getPrice()));
            msg.exec();

            if (ticket->getFlight()->isPassengerEnough())
            {
                QString s3 = "Flight ";
                QString s4 = " Now Has Enough Tickets!";
                QMessageBox msg;
                msg.setText(s3 + ticket->getFlight()->getSerial() + s4);
                msg.exec();
            }
        }
    }
    catch (invalid_argument e)
    {
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }


}

void AddTicket::on_btnCancel_clicked()
{
    this->close();
}
