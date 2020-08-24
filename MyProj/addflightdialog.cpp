#include "addflightdialog.h"
#include "ui_addflightdialog.h"
#include "Flight.h"
#include "Employee.h"
#include "Pilot.h"
#include "Host.h"
#include "Recorder.h"
#include "Airline.h"
#include <QMessageBox>
#include <stdexcept>
using namespace std;

AddFlightDialog::AddFlightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFlightDialog)
{
    ui->setupUi(this);

    foreach (Airline* a, Recorder<Airline>::getInstance()->get_dataList())
    {
        ui->comboAirline->addItem(a->getName());
    }
}

AddFlightDialog::~AddFlightDialog()
{
    delete ui;
}

void AddFlightDialog::on_btnSubmit_clicked()
{
    Flight* flight = nullptr;
    try
    {
        QString serial = ui->txtFlightSerial->text();
        QString source = ui->txtSource->text();
        QString dest = ui->txtDest->text();
        QDateTime dep = ui->dttmDeparture->dateTime();
        QDateTime arr = ui->dttmArrival->dateTime();
        int num_hosts = ui->spnHosts->value();
        int capacity = ui->spnPassengers->value();
        Airline* currentAirline = Recorder<Airline>::getInstance()->get_dataList()[ui->comboAirline->currentIndex()];
        if (dep < QDateTime::currentDateTime())
            throw invalid_argument("DateTime Of This Flight Has Passed!\n"
                                     "Can Not Add This Flight!!");

        flight = new Flight(serial, currentAirline, source,
                                    dest, dep, arr, num_hosts, capacity);

        Recorder<Flight>::getInstance()->add(flight);

        QMessageBox msg;
        QString str = "Submit Successfully!\n";

        msg.setText(str);
        msg.exec();
    }

    catch (invalid_argument e)
    {
        delete flight;
        flight = nullptr;
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }
}

void AddFlightDialog::on_btnCancel_clicked()
{
    this->close();
}
