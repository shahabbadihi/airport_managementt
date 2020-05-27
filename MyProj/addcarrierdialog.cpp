#include "addcarrierdialog.h"
#include "ui_addcarrierdialog.h"
#include "Carrier.h"
#include "Recorder.h"
#include "Airline.h"

AddCarrierDialog::AddCarrierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCarrierDialog)
{
    ui->setupUi(this);

    foreach (Airline* a, Recorder<Airline>::get_dataList())
    {
        ui->comboAirline->addItem(a->getName());
    }
}

AddCarrierDialog::~AddCarrierDialog()
{
    delete ui;
}

void AddCarrierDialog::on_btnSubmit_clicked()
{
    Carrier* carrier = new Carrier;
    Airline* currentAirline = Recorder<Airline>::get_dataList()[ui->comboAirline->currentIndex()];
    carrier->setSerial(ui->txtSerial->text());
    carrier->setAirline(currentAirline);
}

void AddCarrierDialog::on_btnCancel_clicked()
{
    this->close();
}
