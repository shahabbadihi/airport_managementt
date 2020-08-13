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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tab_widget(new QTabWidget(this))
{


    ui->setupUi(this);

    //this->timer = new QTimer(this);
    //connect(this->timer, SIGNAL(timeout()), this, SLOT(updateFiles()));
//    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateFlightModel()));
    //timer->start(1000);
//    Recorder<Airline>::getInstance()->import();
//    Recorder<Pilot>::getInstance()->import();
//    Recorder<Host>::getInstance()->import();
//    Recorder<Airplane>::getInstance()->import();
//    Recorder<Carrier>::getInstance()->import();
//    Recorder<Flight>::getInstance()->import();
//    Recorder<Ticket>::getInstance()->import();
//    Recorder<Passenger>::getInstance()->import();





    tab_widget->setStyleSheet("background-color : black;");
    this->setCentralWidget(tab_widget);
    tab_widget->addTab(new FlightTablePage(this), "Flights");
    tab_widget->addTab(new PilotsPage(this), "Pilots");
    tab_widget->addTab(new HostsPage(this), "Hosts");
    tab_widget->addTab(new AirplanesPage(this), "Airplanes");
    //connect(this->model, SIGNAL(dataChanged()), ui->tableView, SLOT(refresh()));

    //ui->tableView.setC
    //ui->tableView->setModel();

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

//void MainWindow::updateFiles()
//{
//    Recorder<Airline>::getInstance()->updateFileAll();
//    Recorder<Airplane>::getInstance()->updateFileAll();
//    Recorder<Host>::getInstance()->updateFileAll();
//    Recorder<Pilot>::getInstance()->updateFileAll();
//    Recorder<Flight>::getInstance()->updateFileAll();
//    Recorder<Passenger>::getInstance()->updateFileAll();
//    Recorder<Ticket>::getInstance()->updateFileAll();
//    Recorder<Carrier>::getInstance()->updateFileAll();
//}


//void MainWindow::updateFlightModel()
//{
//    for (int row = 0; row < Recorder<Flight>::getInstance()->get_dataList().size(); row++)
//    {
//        QModelIndex index0 = this->model->index(row, 0);
//        this->model->setData(index0, Recorder<Flight>::getInstance()->get_dataList()[row]->getAirline()->getName());
//        QModelIndex index1 = this->model->index(row, 1);
//        this->model->setData(index1, Recorder<Flight>::getInstance()->get_dataList()[row]->getSerial());
//        QModelIndex index2 = this->model->index(row, 2);
//        this->model->setData(index2, Recorder<Flight>::getInstance()->get_dataList()[row]->getSource());
//        QModelIndex index3 = this->model->index(row, 3);
//        this->model->setData(index3, Recorder<Flight>::getInstance()->get_dataList()[row]->getDestination());
//        QModelIndex index4 = this->model->index(row, 4);
//        this->model->setData(index4, Recorder<Flight>::getInstance()->get_dataList()[row]->getDateTimeDeparture());
//        QModelIndex index5 = this->model->index(row, 5);
//        this->model->setData(index5, Recorder<Flight>::getInstance()->get_dataList()[row]->getDateTimeArrival());
//    }
//    QModelIndex i1 = this->model->index(0, 0);
//    QModelIndex i2 = this->model->index(, 0);
//    this->model->dataChanged();
//}
//<<<<<<< HEAD
//=======
//void MainWindow::on_actionFlight_triggered()
//{
//    this->deleteFlightDialog=new deleteFlight;
//    deleteFlightDialog->setModal(true);
//    deleteFlightDialog->exec();
//    delete deleteFlightDialog;
//}

//void MainWindow::on_actioncarrier_triggered()
//{
//    this->deleteCarrierDialog=new deleteCarrier;
//    deleteCarrierDialog->setModal(true);
//    deleteCarrierDialog->exec();
//    delete deleteCarrierDialog;
//}

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
