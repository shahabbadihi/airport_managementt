#include "addflightdialog.h"
#include "ui_addflightdialog.h"
#include "Flight.h"
#include "Employee.h"
#include "Pilot.h"
#include "Host.h"
#include <QMessageBox>

AddFlightDialog::AddFlightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFlightDialog)
{
    ui->setupUi(this);
}

AddFlightDialog::~AddFlightDialog()
{
    delete ui;
}

void AddFlightDialog::on_btnSubmit_clicked()
{
    Flight* flight = new Flight();
    flight->setSerial(ui->txtFlightSerial->text().toLong());
    flight->setSource(ui->txtSource->text());
    flight->setDestination(ui->txtDest->text());
    flight->setDateTimeArrival(ui->dttmArrival->dateTime());
    flight->setDateTimeDeparture(ui->dttmDeparture->dateTime());
    flight->setNumOfHosts(ui->spnHosts->value());
    flight->setNumOfPassengers(ui->spnPassengers->value());

    flight->setPilot(Recorder<Pilot>::getFirstFree(flight));
    for (int i = 0; i < flight->getNumOfHosts(); i++)
    {
        flight->attachHost(Recorder<Host>::getFirstFree(flight));
    }

    QMessageBox msg;
    QString str = "Submit Successfully!\n";
    QString str2 = "The Flight's Pilot Is: " + flight->getPilot()->getFname() + " " + flight->getPilot()->getLname() + "\n";
    QString str3 = "The Flight's Hosts Are:\n";
    foreach (Host* h, flight->getHostsList())
    {
        str3 += h->getFname() + " " + h->getLname() + "\n";
    }
    msg.setText(str + str2 + str3);
    msg.exec();
}

void AddFlightDialog::on_btnCancel_clicked()
{
    this->close();
}
