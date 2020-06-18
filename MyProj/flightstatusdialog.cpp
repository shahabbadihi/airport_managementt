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
    ui(new Ui::FlightStatusDialog),
    flight_ptr(flight)
{
    ui->setupUi(this);
    connect(flight, SIGNAL(flightStatusChanged()), this, SLOT(reset()));

    ui->lblFlightSerial->setText("Flight " + flight->getSerial());
    ui->lblFromTo->setText("From " + flight->getSource() + " To " + flight->getDestination());

    ui->lblPilotStatus->setText(flight_ptr->isPilotSetted() ? "Setted!" : "Not Setted!");
    ui->lblHostsStatus->setText(flight_ptr->isHostEnough() ? "Enough!" : "Not Enough!");
    ui->lblAirplaneStatus->setText(flight_ptr->isAirplaneSetted() ? "Setted!" : "Not Setted!");
    ui->lblDepartureCarrierStatus->setText(flight_ptr->isDepartureCarrierSetted() ? "Setted!" : "Not Setted!");
    ui->lblArrivalCarrierStatus->setText(flight_ptr->isArrivalCarrierSetted() ? "Setted!" : "Not Setted!");
    ui->lblTicketsStatus->setText(flight_ptr->isPassengerEnough() ? "Enough!" : "Not Enough!");
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

void FlightStatusDialog::reset()
{
    ui->lblPilotStatus->setText(flight_ptr->isPilotSetted() ? "Setted!" : "Not Setted!");
    ui->lblHostsStatus->setText(flight_ptr->isHostEnough() ? "Enough!" : "Not Enough!");
    ui->lblAirplaneStatus->setText(flight_ptr->isAirplaneSetted() ? "Setted!" : "Not Setted!");
    ui->lblDepartureCarrierStatus->setText(flight_ptr->isDepartureCarrierSetted() ? "Setted!" : "Not Setted!");
    ui->lblArrivalCarrierStatus->setText(flight_ptr->isArrivalCarrierSetted() ? "Setted!" : "Not Setted!");
    ui->lblTicketsStatus->setText(flight_ptr->isPassengerEnough() ? "Enough!" : "Not Enough!");
}
