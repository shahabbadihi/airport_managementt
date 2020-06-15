#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "delaydialog.h"
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
#include <QSignalMapper>
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
#include "deleteticket.h"

template <class T>
Recorder<T>* Recorder<T>::instance;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
{
    ui->setupUi(this);

    this->flight_table_model = FlightTableModel::getInstance();
    connect(flight_table_model, SIGNAL(recordInsertedSignal(int)), this, SLOT(addButtonFlightTable(int)));
    connect(flight_table_model, SIGNAL(recordRemovedSignal(int)), this, SLOT(removeButtonFlightTable(int)));

    ui->tableView->setModel(flight_table_model);
    //ui->tableView->setItemDelegateForColumn(7, delegate);
    //ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setColumnWidth(0, 80);
    ui->tableView->setColumnWidth(1, 80);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 100);

    signal_mapper = new QSignalMapper(this);
    for (int i = 0; i < flight_table_model->rowCount(); i++)
    {
        delay_buttons.push_back(new QPushButton("Delay", ui->tableView));
//        connect(delay_buttons[i], SIGNAL(clicked()), this, SLOT(showDelayDialog()));
        ui->tableView->setIndexWidget(flight_table_model->index(i, 7), delay_buttons[i]);
        signal_mapper->setMapping(delay_buttons[i], i);

        connect(delay_buttons[i], SIGNAL(clicked()), signal_mapper, SLOT(map()));
    }
    connect(signal_mapper, SIGNAL(mapped(int)), this, SLOT(showDelayDialog(int)));

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

    connect(this->pilot_mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtonsPilot(int)));

    connect(ui->btnNextPilot, SIGNAL(clicked()), this->pilot_mapper, SLOT(toNext()));
    connect(ui->btnPrePilot, SIGNAL(clicked()), this->pilot_mapper, SLOT(toPrevious()));

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
    ui->lblClock->setText(QDateTime::currentDateTime().toString());
}

void MainWindow::updateFlightState()
{
    foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
    {
        f->setState();
    }
}

void MainWindow::updateButtonsPilot(int row)
{
    ui->btnPrePilot->setEnabled(row > 0);
    ui->btnNextPilot->setEnabled(row < pilot_item_model->rowCount() - 1);
}

void MainWindow::addButtonFlightTable(int row)
{
    this->delay_buttons.push_back(new QPushButton("Delay", ui->tableView));
    ui->tableView->setIndexWidget(this->flight_table_model->index(row, 7), delay_buttons[row]);

    signal_mapper->setMapping(delay_buttons[row], row);
    connect(delay_buttons[row], SIGNAL(clicked()), signal_mapper, SLOT(map()));
}

void MainWindow::removeButtonFlightTable(int row)
{
    disconnect(delay_buttons[row], SIGNAL(clicked()), signal_mapper, SLOT(map()));
    delete delay_buttons[row];


    signal_mapper->removeMappings(delay_buttons[row]);
    this->delay_buttons.remove(row);


}

void MainWindow::showDelayDialog(int row)
{
    int res;
    DelayDialog d(this);
    d.setWindowTitle("Set Delay");
    res = d.exec();

    if (res == QDialog::Rejected)
    {
        return;
    }
    if (res == QDialog::Accepted)
    {
        Recorder<Flight>::getInstance()->get_dataList()[row]->delay(d.milli_delay());
    }
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
