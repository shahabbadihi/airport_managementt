#include "addcarrierdialog.h"
#include "ui_addcarrierdialog.h"
#include "Carrier.h"
#include "Recorder.h"
#include "Airline.h"
#include <stdexcept>
using namespace std;

AddCarrierDialog::AddCarrierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCarrierDialog)
{
    ui->setupUi(this);

//    foreach (Airline* a, Recorder<Airline>::getInstance()->get_dataList())
//    {
//        ui->comboAirline->addItem(a->getName());
//    }
}

AddCarrierDialog::~AddCarrierDialog()
{
    delete ui;
}

void AddCarrierDialog::on_btnSubmit_clicked()
{
    Carrier* carrier = nullptr;
    try
    {
        //Carrier* carrier = new Carrier;
        carrier = new Carrier(ui->txtSerial->text(), ui->txtPlace->text());
        //Airline* currentAirline = Recorder<Airline>::getInstance()->get_dataList()[ui->comboAirline->currentIndex()];
        //carrier->setSerial(ui->txtSerial->text());
        //carrier->setPlace(ui->txtPlace->text());
        //carrier->setAirline(currentAirline);

        Recorder<Carrier>::getInstance()->add(carrier);

        QMessageBox msg;
        msg.setText("Submit Successfully!");
        msg.exec();
    }

    catch (invalid_argument e)
    {
        delete carrier;
        carrier = nullptr;
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }
}

void AddCarrierDialog::on_btnCancel_clicked()
{
    this->close();
}


