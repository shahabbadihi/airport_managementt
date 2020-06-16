#include "flightstatusdialog.h"
#include "ui_flightstatusdialog.h"
#include "Flight.h"
#include "addairplanedialog.h"
#include "addhost.h"
#include "addticket.h"
#include "addcarrierdialog.h"
#include "dialog.h"

FlightStatusDialog::FlightStatusDialog(Flight* flight, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlightStatusDialog)
{
    ui->setupUi(this);

    ui->lblFlightSerial->setText("Flight " + flight->getSerial());
    ui->lblFromTo->setText("From " + flight->getSource() + " To " + flight->getDestination());

    ui->lblPilotStatus->setText(flight->isPilotSetted() ? "Setted!" : "Not Setted!");
    ui->lblHostsStatus->setText(flight->isHostEnough() ? "Enough!" : "Not Enough!");
    ui->lblAirplaneStatus->setText(flight->isAirplaneSetted() ? "Setted!" : "Not Setted!");
    ui->lblDepartureCarrierStatus->setText(flight->isDepartureCarrierSetted() ? "Setted!" : "Not Setted!");
    ui->lblArrivalCarrierStatus->setText(flight->isArrivalCarrierSetted() ? "Setted!" : "Not Setted!");
    ui->lblTicketsStatus->setText(flight->isPassengerEnough() ? "Enough!" : "Not Enough!");
}

FlightStatusDialog::~FlightStatusDialog()
{
    delete ui;
}

void FlightStatusDialog::on_btnAddPilot_clicked()
{
    Dialog * addPilotDialog = new Dialog();
    addPilotDialog->setModal(true);
    addPilotDialog->exec();
    delete addPilotDialog;
}

void FlightStatusDialog::on_btnAddHost_clicked()
{
    AddHost * addHostDialog = new AddHost();
    addHostDialog->setModal(true);
    addHostDialog->exec();
    delete addHostDialog;
}

void FlightStatusDialog::on_btnAddAirplane_clicked()
{
    AddAirplaneDialog * addAirplaneDialog = new AddAirplaneDialog();
    addAirplaneDialog->setModal(true);
    addAirplaneDialog->exec();
    delete addAirplaneDialog;
}

void FlightStatusDialog::on_btnAddDCarrier_clicked()
{
    AddCarrierDialog * addCarrierDialog = new AddCarrierDialog();
    addCarrierDialog->setModal(true);
    addCarrierDialog->exec();
    delete addCarrierDialog;
}

void FlightStatusDialog::on_btnAddACarrier_clicked()
{
    AddCarrierDialog * addCarrierDialog = new AddCarrierDialog();
    addCarrierDialog->setModal(true);
    addCarrierDialog->exec();
    delete addCarrierDialog;
}

void FlightStatusDialog::on_btnAddTicket_clicked()
{
    AddTicket * addTicketDialog = new AddTicket();
    addTicketDialog->setModal(true);
    addTicketDialog->exec();
    delete addTicketDialog;
}
