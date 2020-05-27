#include "addflightdialog.h"
#include "ui_addflightdialog.h"
#include "Flight.h"
#include "Employee.h"
#include "Pilot.h"
#include "Host.h"
#include "Recorder.h"
#include "Airline.h"
#include <QMessageBox>

template <class T>
QVector<T*> Recorder<T>::dataList;

AddFlightDialog::AddFlightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFlightDialog)
{
    ui->setupUi(this);

    foreach (Airline* a, Recorder<Airline>::get_dataList())
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
    try
    {
        Flight* flight = new Flight();
        Airline* currentAirline = Recorder<Airline>::get_dataList()[ui->comboAirline->currentIndex()];
        flight->setAirline(currentAirline);
        flight->setSerial(ui->txtFlightSerial->text());
        flight->setSource(ui->txtSource->text());
        flight->setDestination(ui->txtDest->text());
        flight->setDateTimeArrival(ui->dttmArrival->dateTime());
        flight->setDateTimeDeparture(ui->dttmDeparture->dateTime());
        flight->setNumOfHosts(ui->spnHosts->value());
        flight->setNumOfPassengers(ui->spnPassengers->value());

        flight->setPilot(currentAirline->getFirstFreePilot(flight));

        for (int i = 0; i < flight->getNumOfHosts(); i++)
        {
            flight->attachHost(currentAirline->getFirstFreeHost(flight));
        }

        if (flight->getPilot() == nullptr)
        {
            QMessageBox msg;
            msg.setText("There Is No Free Pilot!");
            msg.exec();
            delete flight;
            flight = nullptr;
            return;
        }
        foreach (Host* h, flight->getHostsList())
        {
            if (h == nullptr)
            {
                QMessageBox msg;
                msg.setText("Not Enough Hosts!");
                msg.exec();
                delete flight;
                flight = nullptr;
                return;
            }
        }
        Recorder<Flight>::add(flight);

        QMessageBox msg;
        QString str = "Submit Successfully!\n";
        QString str2 = "The Flight's Pilot Is: " + flight->getPilot()->getFname() + " " + flight->getPilot()->getLname() + "\n";
        QString str3 = "The Flight's Hosts Are:\n";
        foreach (Host* h, flight->getHostsList())
        {
            str3 += h->getFname() + " " + h->getLname() + "\n";
        }
        msg.setText(str + str2 + str3);
        msg.exec();
    }
    catch (QException e)
    {

    }
}

void AddFlightDialog::on_btnCancel_clicked()
{
    this->close();
}
