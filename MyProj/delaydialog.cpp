#include "delaydialog.h"
#include "ui_delaydialog.h"

DelayDialog::DelayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelayDialog)
{
    ui->setupUi(this);
}

DelayDialog::~DelayDialog()
{
    delete ui;
}

qint64 DelayDialog::milli_delay()
{
    return (ui->spnHour->value() * 60 * 60 + ui->spnMinute->value() * 60) * 1000;
}

void DelayDialog::on_buttonBox_accepted()
{
    this->accept();
}

void DelayDialog::on_buttonBox_rejected()
{
    this->reject();
}
