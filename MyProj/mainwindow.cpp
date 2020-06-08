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
#include <QHeaderView>
#include <QTime>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include "flighttablemodel.h"
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
    , timer(new QTimer(this))
{
    ui->setupUi(this);

    this->flight_table_model = FlightTableModel::getInstance();


    ui->tableView->setModel(flight_table_model);

    this->pilot_mapper = new QDataWidgetMapper(this);
    this->pilot_item_model = PilotItemModel::getInstance();
    pilot_mapper->setModel(pilot_item_model);
    pilot_mapper->addMapping(ui->txtNamePilot, 0);
    pilot_mapper->addMapping(ui->txtFamilyPilot, 1);
    pilot_mapper->addMapping(ui->txtNationalCodePilot, 2);
    pilot_mapper->addMapping(ui->txtPersonnelCodePilot, 3);
    pilot_mapper->addMapping(ui->txtAirlinePilot, 4);
    pilot_mapper->addMapping(ui->dtBirthDatePliot, 5);
    pilot_mapper->addMapping(ui->dtEmploymentDatePilot, 6);
    pilot_mapper->addMapping(ui->plainTextEdit, 7);
    pilot_mapper->addMapping(ui->txtDegreePilot, 8);
    pilot_mapper->toFirst();

    connect(ui->btnNextPilot, SIGNAL(clicked()), this->pilot_mapper, SLOT(toNext()));
    connect(ui->btnPrePilot, SIGNAL(clicked()), this->pilot_mapper, SLOT(toPrevious()));

    connect(this->pilot_mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtonsPilot(int)));

    //this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(showClock()));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateFiles()));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateFlightState()));
//    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateFlightModel()));
    timer->start(1000);

    //connect(this->model, SIGNAL(dataChanged()), ui->tableView, SLOT(refresh()));

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
            if (f->getFlightState() != CANCELED && f->getFlightState() != SUSPENDED)
            {
                f->setFlightState(ONAIR);
            }
        }

        if (f->getDateTimeArrival() >= QDateTime::currentDateTime())
        {
            f->setFlightState(DONE);
        }

//        if ((f->getFlightState() == SUSPENDED || f->getFlightState() == DELAYED) &&
//                f->getDateTimeDeparture().msecsTo(QDateTime::currentDateTime()) <= 10 * 60 * 1000)
//        {
//            f->delay(30 * 60 * 1000);
//            f->setFlightState(DELAYED);
//        }

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

void MainWindow::updateButtonsPilot(int row)
{
    ui->btnPrePilot->setEnabled(row > 0);
    ui->btnNextPilot->setEnabled(row < pilot_item_model->rowCount() - 1);
}

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
