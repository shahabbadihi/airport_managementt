#include "addticket.h"
#include "ui_addticket.h"
#include "Ticket.h"
#include "Recorder.h"
#include "Flight.h"
#include "Passenger.h"
#include "p2_12.h"
#include "pu2.h"
#include "po12.h"
#include "getpassengerfactory.h"
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
    try
    {
        Ticket* ticket = nullptr;
        foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
        {
            if (f->getSource() == ui->txtSource->text() &&
                    f->getDestination() == ui->txtDest->text() &&
                    f->getDateTimeDeparture().date() == ui->dtDate->date() &&
                    f->getNumOfPassengers() < f->getCapacity())
            {
                ticket = new Ticket();
                ticket->setNo(ui->txtNo->text().toLong());
                //ticket->setSource(ui->txtSource->text());
                //ticket->setDestination(ui->txtDest->text());

                Passenger* passenger = nullptr;

                int age = ui->dtDate->date().year() - ui->dtBirthDate->date().year();
                if (ui->dtBirthDate->date() > ui->dtDate->date().addYears(-age))
                    age--;

                if (age < 2)
                {
                    passenger = GetPassengerFactory::getInstance()->getPassenger(ui->dtBirthDate->date(),
                                                                                 ui->dtDate->date(),
                                                                                 ui->txtNationalCode->text() + "A");
                }
                else if (age >= 2 && age <= 12)
                {
                    passenger = GetPassengerFactory::getInstance()->getPassenger(ui->dtBirthDate->date(),
                                                                                 ui->dtDate->date(),
                                                                                 ui->txtNationalCode->text() + "B");
                }
                else if (age > 12)
                {
                    passenger = GetPassengerFactory::getInstance()->getPassenger(ui->dtBirthDate->date(),
                                                                                 ui->dtDate->date(),
                                                                                 ui->txtNationalCode->text() + "C");
                }

                passenger->setNationalCode(ui->txtNationalCode->text().toLong());
                passenger->setFname(ui->txtFName->text());
                passenger->setLname(ui->txtLName->text());
                passenger->setBirthDate(ui->dtBirthDate->date());
                passenger->setFatherName(ui->txtPassFatherName->text());

                passenger->attachTicket(ticket);

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
    QDateTime departure = ticket->getFlight()->getDateTimeDeparture().time();
    QDateTime destination = ticket->getFlight()->getDateTimeDestination().time();
    double seconds = departure.secsTo(destination);
    ticket->setPrice((seconds * 5) / 72);

}

void AddTicket::on_btnCancel_clicked()
{
    this->close();
}
