#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "addhost.h"
#include "deletehost.h"
#include "deletepilot.h"
#include "addflightdialog.h"
#include "addairplanedialog.h"
#include "addticket.h"
#include <QString>
#include <QDesktopWidget>
#include <QHeaderView>
#include <QTime>
#include "Recorder.h"
#include "Airline.h"
#include "Airplane.h"
#include "Host.h"
#include "Pilot.h"
#include "Passenger.h"
#include "Carrier.h"
#include "Flight.h"
#include "Ticket.h"

template <class T>
Recorder<T>* Recorder<T>::instance;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(showClock()));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateFiles()));
    //connect(this->timer, SIGNAL(timeout()), this, SLOT(print()));
    timer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAddPilot_triggered()
{
    this->addPilotDialog = new Dialog();
    addPilotDialog->setModal(true);
    addPilotDialog->exec();
    delete addPilotDialog;
}

void MainWindow::on_actionAdd_Host_triggered()
{
    this->addHostDialog = new AddHost();
    addHostDialog->setModal(true);
    addHostDialog->exec();
    delete addHostDialog;
}

void MainWindow::on_actionDeleteHost_triggered()
{
    this->deleteHostDialog = new deleteHost();
    deleteHostDialog->setModal(true);
    deleteHostDialog->exec();
    delete deleteHostDialog;
}

void MainWindow::on_actionAddFlight_triggered()
{
    this->addFlightDialog = new AddFlightDialog();
    addFlightDialog->setModal(true);
    addFlightDialog->exec();
    delete addFlightDialog;
}

void MainWindow::on_actionAddTicket_triggered()
{
    this->addTicketDialog = new AddTicket();
    addTicketDialog->setModal(true);
    addTicketDialog->exec();
    delete addTicketDialog;
}

void MainWindow::on_actionAddAirline_triggered()
{
    this->addAirlineDialog = new AddAirlineDialog();
    addAirlineDialog->setModal(true);
    addAirlineDialog->exec();
    delete addAirlineDialog;
}

void MainWindow::on_actionAddAirplane_triggered()
{
    this->addAirplaneDialog = new AddAirplaneDialog();
    addAirplaneDialog->setModal(true);
    addAirplaneDialog->exec();
    delete addAirplaneDialog;
}

void MainWindow::on_actionDeletePilot_triggered()
{
    this->deletePilotDialog = new DeletePilot();
    deletePilotDialog->setModal(true);
    deletePilotDialog->exec();
    delete deletePilotDialog;
}

void MainWindow::on_actionAddCarrier_triggered()
{
    this->addCarrierDialog = new AddCarrierDialog();
    addCarrierDialog->setModal(true);
    addCarrierDialog->exec();
    delete addCarrierDialog;
}

void MainWindow::updateFiles()
{
    Recorder<Airline>::getInstance()->updateFileAll();
    Recorder<Airplane>::getInstance()->updateFileAll();
    Recorder<Host>::getInstance()->updateFileAll();
    Recorder<Pilot>::getInstance()->updateFileAll();
    Recorder<Flight>::getInstance()->updateFileAll();
    Recorder<Passenger>::getInstance()->updateFileAll();
    Recorder<Ticket>::getInstance()->updateFileAll();
    Recorder<Carrier>::getInstance()->updateFileAll();
}

void MainWindow::showClock()
{
    ui->lblClock->setText(QTime::currentTime().toString());
}
