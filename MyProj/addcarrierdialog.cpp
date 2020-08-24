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
        carrier = new Carrier(ui->txtSerial->text(), ui->txtPlace->text());

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


