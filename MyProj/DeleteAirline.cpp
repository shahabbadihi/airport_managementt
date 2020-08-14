#include "DeleteAirline.h"
#include "ui_DeleteAirline.h"

DeleteAirline::DeleteAirline(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteAirline)
{
    ui->setupUi(this);

    this->model = AirlineItemModel::getInstance();
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(0);
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
    int index = ui->comboBox->currentIndex();

    if (index == this->model->rowCount() - 1)
    {
        ui->comboBox->setCurrentIndex(index - 1);
    }
    this->model->removeRows(index, 1);
    return;
}
