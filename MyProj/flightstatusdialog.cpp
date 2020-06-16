#include "flightstatusdialog.h"
#include "ui_flightstatusdialog.h"

FlightStatusDialog::FlightStatusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlightStatusDialog)
{
    ui->setupUi(this);
}

FlightStatusDialog::~FlightStatusDialog()
{
    delete ui;
}
