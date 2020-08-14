#include "DeleteAirline.h"
#include "ui_DeleteAirline.h"

DeleteAirline::DeleteAirline(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteAirline)
{
    ui->setupUi(this);
}

DeleteAirline::~DeleteAirline()
{
    delete ui;
}

void DeleteAirline::on_btnCancel_clicked()
{
    this->close();
}

void DeleteAirline::on_btnSubmit_clicked()
{

}
