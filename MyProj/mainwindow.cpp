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
    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateFlightState()));
    timer->start(1000);

    //ui->tableView.setC
    //ui->tableView->setModel();
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

void MainWindow::updateFlightState()
{
    foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
    {
        if (f->getDateTimeDeparture() <= QDateTime::currentDateTime() &&
                QDateTime::currentDateTime() < f->getDateTimeArrival())
        {
            f->setFlightState(ONAIR);
        }

        if (f->getDateTimeArrival() >= QDateTime::currentDateTime())
        {
            f->setFlightState(DONE);
        }

        if ((f->getFlightState() == SUSPENDED || f->getFlightState() == DELAYED) &&
                f->getDateTimeDeparture().msecsTo(QDateTime::currentDateTime()) <= 10 * 60 * 1000)
        {
            f->delay(30 * 60 * 1000);
            f->setFlightState(DELAYED);
        }

        if (f->isPilotSetted() && f->isHostEnough() && f->isAirplaneSetted() &&
                f->isArrivalCarrierSetted() && f->isDepartureCarrierSetted() &&
                f->isPassengerEnough())
        {
            f->setFlightState(READY);
        }

        if (!f->isPilotSetted())
        {
            f->setFlightState(SUSPENDED);
            f->setPilot(f->getAirline()->getFirstFreePilot(f));
        }

        if (!f->isHostEnough())
        {
            f->setFlightState(SUSPENDED);
            f->attachHost(f->getAirline()->getFirstFreeHost(f));
        }

        if (!f->isAirplaneSetted())
        {
            f->setFlightState(SUSPENDED);
            f->setAirplane(f->getAirline()->getFirstFreeAirplane(f));
        }

        if (!f->isArrivalCarrierSetted())
        {
            f->setFlightState(SUSPENDED);
            f->setArrival_carrier(Recorder<Carrier>::getInstance()->getFirstFree(f->getDateTimeArrival(),
                                                                                 f->getDestination()));
        }

        if (!f->isDepartureCarrierSetted())
        {
            f->setFlightState(SUSPENDED);
            f->setDeparture_carrier(Recorder<Carrier>::getInstance()->getFirstFree(f->getDateTimeDeparture(),
                                                                                 f->getSource()));
        }

        if (!f->isPassengerEnough())
        {
            f->setFlightState(SUSPENDED);
        }
    }
}
