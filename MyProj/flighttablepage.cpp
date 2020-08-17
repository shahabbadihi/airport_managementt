#include "flighttablepage.h"
#include "ui_flighttablepage.h"
#include "delaydialog.h"
#include "Recorder.h"
#include "Flight.h"
#include "flightstatusdialog.h"
#include "ThreadedJob.h"
#include <QDialog>
#include <QThread>
#include "detailspage.h"
FlightTablePage::FlightTablePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlightTablePage),
    timer(new QTimer(this))
{
    connect(this->timer, SIGNAL(timeout()), this, SLOT(showClock()));
    timer->start(1000);

    ui->setupUi(this);

    this->flight_table_model = FlightTableModel::getInstance();
    connect(flight_table_model, SIGNAL(recordInsertedSignal(int)), this, SLOT(addButtonFlightTable(int)));
    connect(flight_table_model, SIGNAL(recordRemovedSignal(int)), this, SLOT(removeButtonFlightTable(int)));

    this->proxy = new QSortFilterProxyModel(this);
    this->proxy->setSourceModel(flight_table_model);
    this->proxy->setFilterKeyColumn(4);
    this->proxy->setDynamicSortFilter(true);

    ui->tableView->setModel(proxy);

    //ui->tableView->setItemDelegateForColumn(7, delegate);
    //ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setColumnWidth(0, 80);
    ui->tableView->setColumnWidth(1, 80);
    ui->tableView->setColumnWidth(2, 80);
    ui->tableView->setColumnWidth(3, 80);
    ui->tableView->setColumnWidth(4, 130);
    ui->tableView->setColumnWidth(5, 130);
    ui->tableView->setColumnWidth(6, 100);
    ui->tableView->setColumnWidth(7, 45);
    ui->tableView->setColumnWidth(8, 45);
    ui->tableView->setColumnWidth(9, 45);


    signal_mapper_delay = new QSignalMapper(this);
    signal_mapper_status = new QSignalMapper(this);
    signal_mapper_details = new QSignalMapper(this);

    for (int i = 0; i < flight_table_model->rowCount(); i++)
    {
        delay_buttons.push_back(new QPushButton("Delay", ui->tableView));
        status_buttons.push_back(new QPushButton("Status", ui->tableView));
        details_buttons.push_back(new QPushButton("Details", ui->tableView));

//        connect(delay_buttons[i], SIGNAL(clicked()), this, SLOT(showDelayDialog()));
        ui->tableView->setIndexWidget(proxy->index(i, 7), delay_buttons[i]);
        ui->tableView->setIndexWidget(proxy->index(i, 8), status_buttons[i]);
        ui->tableView->setIndexWidget(proxy->index(i, 9), details_buttons[i]);

        if (Recorder<Flight>::getInstance()->get_dataList()[i]->getFlightState()
                == DONE)
        {
            delay_buttons[i]->setDisabled(true);
            status_buttons[i]->setDisabled(true);
        }
//        connect(Recorder<Flight>::getInstance()->get_dataList()[i],
//                SIGNAL(flightDoneSignal(bool)), delay_buttons[i], SLOT(setDisabled(bool)));

        signal_mapper_delay->setMapping(delay_buttons[i], i);
        signal_mapper_status->setMapping(status_buttons[i], i);
        signal_mapper_details->setMapping(details_buttons[i], i);

        connect(delay_buttons[i], SIGNAL(clicked()), signal_mapper_delay, SLOT(map()));
        connect(status_buttons[i], SIGNAL(clicked()), signal_mapper_status, SLOT(map()));
        connect(details_buttons[i], SIGNAL(clicked()), signal_mapper_details, SLOT(map()));

    }
    connect(signal_mapper_delay, SIGNAL(mapped(int)), this, SLOT(showDelayDialog(int)));
    connect(signal_mapper_status, SIGNAL(mapped(int)), this, SLOT(showStatusDialog(int)));
    connect(signal_mapper_details, SIGNAL(mapped(int)), this, SLOT(showDetailsDialog(int)));


    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(4, Qt::DescendingOrder);


    QThread * th_update_flight_table = new QThread();
    ThreadedJob * tj_update_flight_table = new ThreadedJob();
    tj_update_flight_table->moveToThread(th_update_flight_table);

    connect(th_update_flight_table, SIGNAL(started()), tj_update_flight_table,
            SLOT(slt_start_update_flight_table()));

    th_update_flight_table->start();

//    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateFlightState()));


}

FlightTablePage::~FlightTablePage()
{
    delete ui;
}

void FlightTablePage::showClock()
{
    ui->lblClock->setText(QDateTime::currentDateTime().toString());
}

//void FlightTablePage::updateFlightState()
//{
//    foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
//    {
//        f->setState();
//    }
//}

void FlightTablePage::addButtonFlightTable(int row)
{
//    delete proxy;
//    this->proxy = new QSortFilterProxyModel(this);
//    this->proxy->setSourceModel(flight_table_model);
//    this->proxy->setFilterKeyColumn(4);
//    this->proxy->setDynamicSortFilter(true);

//    ui->tableView->setModel(proxy);

//    for (int i = 0; i < flight_table_model->rowCount() - 1; i++)
//    {
//        ui->tableView->setIndexWidget(proxy->index(i, 7), delay_buttons[i]);
//        ui->tableView->setIndexWidget(proxy->index(i, 8), status_buttons[i]);
//    }

    this->proxy->setSortRole(Qt::InitialSortOrderRole);
    this->proxy->invalidate();

    this->delay_buttons.push_back(new QPushButton("Delay", ui->tableView));
    this->status_buttons.push_back(new QPushButton("Status", ui->tableView));
    this->details_buttons.push_back(new QPushButton("Details", ui->tableView));

    ui->tableView->setIndexWidget(this->proxy->index(row, 7), delay_buttons[row]);
    ui->tableView->setIndexWidget(this->proxy->index(row, 8), status_buttons[row]);
    ui->tableView->setIndexWidget(this->proxy->index(row, 9), details_buttons[row]);

    connect(Recorder<Flight>::getInstance()->get_dataList()[row],
            SIGNAL(flightDoneSignal(bool)), delay_buttons[row], SLOT(setDisabled(bool)));
    connect(Recorder<Flight>::getInstance()->get_dataList()[row],
            SIGNAL(flightDoneSignal(bool)), status_buttons[row], SLOT(setDisabled(bool)));

    signal_mapper_delay->setMapping(delay_buttons[row], row);
    signal_mapper_status->setMapping(status_buttons[row], row);
    signal_mapper_details->setMapping(details_buttons[row], row);

    connect(delay_buttons[row], SIGNAL(clicked()), signal_mapper_delay, SLOT(map()));
    connect(status_buttons[row], SIGNAL(clicked()), signal_mapper_status, SLOT(map()));
    connect(details_buttons[row], SIGNAL(clicked()), signal_mapper_details, SLOT(map()));

    this->proxy->setSortRole(Qt::DisplayRole);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(4, Qt::DescendingOrder);
}

void FlightTablePage::removeButtonFlightTable(int row)
{
    disconnect(delay_buttons[row], SIGNAL(clicked()), signal_mapper_delay, SLOT(map()));
    disconnect(status_buttons[row], SIGNAL(clicked()), signal_mapper_status, SLOT(map()));
    disconnect(details_buttons[row], SIGNAL(clicked()), signal_mapper_details, SLOT(map()));
    disconnect(Recorder<Flight>::getInstance()->get_dataList()[row],
            SIGNAL(flightDoneSignal(bool)), delay_buttons[row], SLOT(setDisabled(bool)));
    disconnect(Recorder<Flight>::getInstance()->get_dataList()[row],
            SIGNAL(flightDoneSignal(bool)), status_buttons[row], SLOT(setDisabled(bool)));

    delete delay_buttons[row];
    delete status_buttons[row];
    delete details_buttons[row];

    signal_mapper_delay->removeMappings(delay_buttons[row]);
    signal_mapper_status->removeMappings(status_buttons[row]);
    signal_mapper_details->removeMappings(details_buttons[row]);

    this->delay_buttons.remove(row);
    this->status_buttons.remove(row);
    this->details_buttons.remove(row);

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
void FlightTablePage::showDetailsDialog(int row)
{
    DetailsPage d(Recorder<Flight>::getInstance()->get_dataList()[row], this);
    d.setWindowTitle("Flight Details");
    d.exec();
}
