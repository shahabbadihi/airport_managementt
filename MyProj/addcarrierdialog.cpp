#include "addcarrierdialog.h"
#include "ui_addcarrierdialog.h"
#include "Carrier.h"
#include "Recorder.h"
#include "Airline.h"

template <class T>
Recorder<T>* Recorder<T>::instance;

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
    Carrier* carrier = new Carrier;
    //Airline* currentAirline = Recorder<Airline>::getInstance()->get_dataList()[ui->comboAirline->currentIndex()];
    carrier->setSerial(ui->txtSerial->text());
    carrier->setPlace(ui->txtPlace->text());
    //carrier->setAirline(currentAirline);

    Recorder<Carrier>::getInstance()->add(carrier);

    QMessageBox msg;
    msg.setText("Submit Successfully!");
    msg.exec();
}

void AddCarrierDialog::on_btnCancel_clicked()
{
    this->close();
}


