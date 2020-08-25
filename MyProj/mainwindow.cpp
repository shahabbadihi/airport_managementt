#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "addhost.h"
#include "deletehost.h"
#include "deletepilot.h"
#include "deleteflight.h"
#include "deletecarrier.h"
#include "addflightdialog.h"
#include "addairplanedialog.h"
#include "addticket.h"
#include <QString>
#include <QTime>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QCloseEvent>
#include <QThread>
#include "Recorder.h"
#include "Airline.h"
#include "Airplane.h"
#include "Host.h"
#include "Pilot.h"
#include "Passenger.h"
#include "Carrier.h"
#include "Flight.h"
#include "Ticket.h"
#include "deleteticket.h"
#include "flighttablepage.h"
#include "pilotspage.h"
#include "HostsPage.h"
#include "AirplanesPage.h"
#include "ThreadedJob.h"
#include "airlinespage.h"

extern bool ISDATACHANGED;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tab_widget(new QTabWidget(this))
{

    ui->setupUi(this);


    foreach (Flight * f, Recorder<Flight>::getInstance()->get_dataList())
    {
        connect(f, SIGNAL(flightStatusMsgSignal(const QString&))
                , ui->statusbar, SLOT(showMessage(const QString&)));
    }

    connect(Recorder<Flight>::getInstance(), SIGNAL(recordAdded()),
            this, SLOT(connectNewFlightToStatusBar()));


    tab_widget->setStyleSheet("background-color : black;");   
    this->setCentralWidget(tab_widget);

    tab_widget->addTab(new FlightTablePage(this), "Flights");
    tab_widget->addTab(new AirlinesPage(this), "Airlines");
    tab_widget->addTab(new PilotsPage(this), "Pilots");
    tab_widget->addTab(new HostsPage(this), "Hosts");
    tab_widget->addTab(new AirplanesPage(this), "Airplanes");


    QThread * th_update = new QThread();
    ThreadedJob * tj_update = new ThreadedJob();
    tj_update->moveToThread(th_update);

    connect(th_update, SIGNAL(started()), tj_update, SLOT(slt_start_update()));

    th_update->start();
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

void MainWindow::on_actionFlight_triggered()
{
    this->deleteFlightDialog=new deleteFlight;
    deleteFlightDialog->setModal(true);
    deleteFlightDialog->exec();
    delete deleteFlightDialog;
}

void MainWindow::on_actioncarrier_triggered()
{
    this->deleteCarrierDialog=new deleteCarrier;
    deleteCarrierDialog->setModal(true);
    deleteCarrierDialog->exec();
    delete deleteCarrierDialog;
}

void MainWindow::on_actionTicket_triggered()
{
    this->deleteTicketDialog=new deleteTicket;
    deleteTicketDialog->setModal(true);
    deleteTicketDialog->exec();
    delete deleteTicketDialog;
}


void MainWindow::on_actionairplane_triggered()
{
    this->deleteAirplaneDialog=new DeleteAirplane;
    deleteAirplaneDialog->setModal(true);
    deleteAirplaneDialog->exec();
    delete deleteAirplaneDialog;
}


void MainWindow::on_actionAirline_triggered()
{
    this->deleteAirlineDialog=new DeleteAirline;
    deleteAirlineDialog->setModal(true);
    deleteAirlineDialog->exec();
    delete deleteAirlineDialog;
}

bool MainWindow::update_files_slot()
{
    if (ISDATACHANGED == false)
    {
        QMessageBox msg;
        msg.setText("Data Have Not Modified!");
        msg.exec();

        return true;
    }

    Recorder<Airline>::getInstance()->updateFileAll();
    Recorder<Airplane>::getInstance()->updateFileAll();
    Recorder<Host>::getInstance()->updateFileAll();
    Recorder<Pilot>::getInstance()->updateFileAll();
    Recorder<Flight>::getInstance()->updateFileAll();
    Recorder<Passenger>::getInstance()->updateFileAll();
    Recorder<Ticket>::getInstance()->updateFileAll();
    Recorder<Carrier>::getInstance()->updateFileAll();

    ISDATACHANGED = false;

    QMessageBox msg;
    msg.setText("Changes Have Been Saved!");
    msg.exec();

    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

bool MainWindow::maybeSave()
{
    if (!ISDATACHANGED)
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Save Changes"),
                               tr("Data has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return update_files_slot();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void MainWindow::connectNewFlightToStatusBar()
{
    connect(Recorder<Flight>::getInstance()->get_dataList().last(),
            SIGNAL(flightStatusMsgSignal(const QString&))
            , ui->statusbar, SLOT(showMessage(const QString&)));
}

void MainWindow::on_actionSave_triggered()
{
    this->update_files_slot();
}

void MainWindow::on_actionSave_Exit_triggered()
{
    this->update_files_slot();
    QMainWindow::close();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
