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
    try
    {
        Flight* flight = new Flight();
        flight->setSerial(ui->txtFlightSerial->text());
        Airline* currentAirline = Recorder<Airline>::getInstance()->get_dataList()[ui->comboAirline->currentIndex()];
        flight->setAirline(currentAirline);

        flight->setSource(ui->txtSource->text());
        flight->setDestination(ui->txtDest->text());
        flight->setDateTimeArrival(ui->dttmArrival->dateTime());
        flight->setDateTimeDeparture(ui->dttmDeparture->dateTime());
        flight->setNumOfHosts(ui->spnHosts->value());
        flight->setCapacity(ui->spnPassengers->value());

        //flight->setPilot(currentAirline->getFirstFreePilot(flight));

    //    for (int i = 0; i < flight->getNumOfHosts(); i++)
    //    {
    //        flight->attachHost(currentAirline->getFirstFreeHost(flight));
    //    }

    //    flight->setAirplane(currentAirline->getFirstFreeAirplane(flight));

    //    flight->setDeparture_carrier(Recorder<Carrier>::getInstance()->getFirstFree(flight->getDateTimeDeparture(),
    //                                                                                flight->getSource()));
    //    flight->setArrival_carrier(Recorder<Carrier>::getInstance()->getFirstFree(flight->getDateTimeArrival(),
    //                                                                              flight->getDestination()));

    //    if (flight->getPilot() == nullptr)
    //    {
    //        QMessageBox msg;
    //        msg.setText("There Is No Free Pilot!");
    //        msg.exec();
    //        delete flight;
    //        flight = nullptr;
    //        return;
    //    }
    //    foreach (Host* h, flight->getHostsList())
    //    {
    //        if (h == nullptr)
    //        {
    //            QMessageBox msg;
    //            msg.setText("Not Enough Hosts!");
    //            msg.exec();
    //            delete flight;
    //            flight = nullptr;
    //            return;
    //        }
    //    }
    //    if (flight->getAirplane() == nullptr)
    //    {
    //        QMessageBox msg;
    //        msg.setText("There Is No Free Airplane!");
    //        msg.exec();
    //        delete flight;
    //        flight = nullptr;
    //        return;
    //    }
    //    if (flight->getDeparture_carrier() == nullptr)
    //    {
    //        QMessageBox msg;
    //        msg.setText("There Is No Free Carrier For Departure!");
    //        msg.exec();
    //        delete flight;
    //        flight = nullptr;
    //        return;
    //    }
    //    if (flight->getArrival_carrier() == nullptr)
    //    {
    //        QMessageBox msg;
    //        msg.setText("There Is No Free Carrier For Arrival!");
    //        msg.exec();
    //        delete flight;
    //        flight = nullptr;
    //        return;
    //    }

        Recorder<Flight>::getInstance()->add(flight);

        QMessageBox msg;
        QString str = "Submit Successfully!\n";
    //    QString str2 = "The Flight's Pilot Is: " + flight->getPilot()->getFname() + " " + flight->getPilot()->getLname() + "\n";
    //    QString str3 = "The Flight's Hosts Are:\n";
    //    foreach (Host* h, flight->getHostsList())
    //    {
    //        str3 += h->getFname() + " " + h->getLname() + "\n";
    //    }
        msg.setText(str/* + str2 + str3*/);
        msg.exec();
    }

    catch (invalid_argument e)
    {
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }
}

void AddFlightDialog::on_btnCancel_clicked()
{
    this->close();
}
