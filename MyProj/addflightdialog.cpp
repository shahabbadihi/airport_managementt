#include "addflightdialog.h"
#include "ui_addflightdialog.h"
#include "Flight.h"

AddFlightDialog::AddFlightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFlightDialog)
{
    ui->setupUi(this);
}

AddFlightDialog::~AddFlightDialog()
{
    delete ui;
}

void AddFlightDialog::on_btnSubmit_clicked()
{
    Flight* flight = new Flight;
    flight->setSerial(ui->txtFlightSerial->text().toLong());
    flight->setSource(ui->txtSource->text());
    flight->setDestination(ui->txtDest->text());
    flight->setDateTimeArrival(ui->dttmArrival->dateTime());
    flight->setDateTimeDeparture(ui->dttmDeparture->dateTime());
}

void AddFlightDialog::on_btnCancel_clicked()
{
    this->close();
}
