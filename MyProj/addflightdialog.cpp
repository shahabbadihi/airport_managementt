#include "addflightdialog.h"
#include "ui_addflightdialog.h"

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
