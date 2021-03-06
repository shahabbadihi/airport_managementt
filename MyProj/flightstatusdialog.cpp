#include "flightstatusdialog.h"
#include "ui_flightstatusdialog.h"
#include "Flight.h"
#include "addairplanedialog.h"
#include "addhost.h"
#include "addticket.h"
#include "addcarrierdialog.h"
#include "dialog.h"
#include "editSeas.h"
FlightStatusDialog::FlightStatusDialog(Flight* flight, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlightStatusDialog),
    flight_ptr(flight)
{
    ui->setupUi(this);
    connect(flight, SIGNAL(flightStatusChanged()), this, SLOT(reset()));

    ui->lblFlightSerial->setText("Flight " + flight->getSerial());
    ui->lblFromTo->setText("From " + flight->getSource() + " To " + flight->getDestination());

    this->reset();
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
    ui->lblTicketsStatus->setText(QString("%1 | %2 of %3").arg(flight_ptr->isPassengerEnough() ? "Enough!" : "Not Enough!").arg(
                                      QString::number(flight_ptr->getNumOfPassengers())).arg
                                  (QString::number(flight_ptr->getCapacity())));
    if(flight_ptr->isCheckInReady()){
        if(flight_ptr->isCheckInCompleted()){
            ui->lblCheckStasus->setText("Completed!");
        }
        else{
            ui->lblCheckStasus->setText("Ready!");
        }

    }
    else{
        ui->lblCheckStasus->setText("Not Ready!");
    }
    ui->btnEditCheck->setDisabled(!flight_ptr->isCheckInReady());
    ui->btnEditCheck->setDisabled(flight_ptr->isCheckInCompleted());

}

void FlightStatusDialog::on_btnEditCheck_clicked()
{
    editSeas * editSeasDialog = new editSeas(flight_ptr);
    editSeasDialog->setModal(true);
    editSeasDialog->exec();
    delete editSeasDialog;
}
