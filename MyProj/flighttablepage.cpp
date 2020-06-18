#include "flighttablepage.h"
#include "ui_flighttablepage.h"
#include "delaydialog.h"
#include "Recorder.h"
#include "Flight.h"
#include "flightstatusdialog.h"
#include <QDialog>

FlightTablePage::FlightTablePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlightTablePage),
    timer(new QTimer(this))
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

    signal_mapper_delay = new QSignalMapper(this);
    signal_mapper_status = new QSignalMapper(this);
    for (int i = 0; i < flight_table_model->rowCount(); i++)
    {
        delay_buttons.push_back(new QPushButton("Delay", ui->tableView));
        status_buttons.push_back(new QPushButton("Status", ui->tableView));
//        connect(delay_buttons[i], SIGNAL(clicked()), this, SLOT(showDelayDialog()));
        ui->tableView->setIndexWidget(flight_table_model->index(i, 7), delay_buttons[i]);
        ui->tableView->setIndexWidget(flight_table_model->index(i, 8), status_buttons[i]);
        signal_mapper_delay->setMapping(delay_buttons[i], i);
        signal_mapper_status->setMapping(status_buttons[i], i);

        connect(delay_buttons[i], SIGNAL(clicked()), signal_mapper_delay, SLOT(map()));
        connect(status_buttons[i], SIGNAL(clicked()), signal_mapper_status, SLOT(map()));
    }
    connect(signal_mapper_delay, SIGNAL(mapped(int)), this, SLOT(showDelayDialog(int)));
    connect(signal_mapper_status, SIGNAL(mapped(int)), this, SLOT(showStatusDialog(int)));

    connect(this->timer, SIGNAL(timeout()), this, SLOT(showClock()));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateFlightState()));

    timer->start(1000);
}

FlightTablePage::~FlightTablePage()
{
    delete ui;
}

void FlightTablePage::showClock()
{
    ui->lblClock->setText(QDateTime::currentDateTime().toString());
}

void FlightTablePage::updateFlightState()
{
    foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
    {
        f->setState();
    }
}

void FlightTablePage::addButtonFlightTable(int row)
{
    this->delay_buttons.push_back(new QPushButton("Delay", ui->tableView));
    ui->tableView->setIndexWidget(this->flight_table_model->index(row, 7), delay_buttons[row]);
    this->status_buttons.push_back(new QPushButton("Status", ui->tableView));
    ui->tableView->setIndexWidget(this->flight_table_model->index(row, 8), status_buttons[row]);

    signal_mapper_delay->setMapping(delay_buttons[row], row);
    connect(delay_buttons[row], SIGNAL(clicked()), signal_mapper_delay, SLOT(map()));
    signal_mapper_status->setMapping(status_buttons[row], row);
    connect(status_buttons[row], SIGNAL(clicked()), signal_mapper_status, SLOT(map()));
}

void FlightTablePage::removeButtonFlightTable(int row)
{
    disconnect(delay_buttons[row], SIGNAL(clicked()), signal_mapper_delay, SLOT(map()));
    disconnect(status_buttons[row], SIGNAL(clicked()), signal_mapper_status, SLOT(map()));
    delete delay_buttons[row];
    delete status_buttons[row];


    signal_mapper_delay->removeMappings(delay_buttons[row]);
    signal_mapper_status->removeMappings(status_buttons[row]);
    this->delay_buttons.remove(row);
    this->status_buttons.remove(row);
}

void FlightTablePage::showDelayDialog(int row)
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

void FlightTablePage::showStatusDialog(int row)
{
    FlightStatusDialog d(Recorder<Flight>::getInstance()->get_dataList()[row], this);
    d.setWindowTitle("Flight Status");
    d.exec();
}
