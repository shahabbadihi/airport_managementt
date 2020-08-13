#include "DeleteAirplane.h"
#include "ui_DeleteAirplane.h"

#include "Recorder.h"
#include "Airplane.h"

DeleteAirplane::DeleteAirplane(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteAirplane)
{
    ui->setupUi(this);

    this->model = AirplaneItemModel::getInstance();
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(0);
}

DeleteAirplane::~DeleteAirplane()
{
    delete ui;
}

void DeleteAirplane::on_btnSubmit_clicked()
{
    int index = ui->comboBox->currentIndex();

    if (index == this->model->rowCount() - 1)
    {
        ui->comboBox->setCurrentIndex(index - 1);
    }
    this->model->removeRows(index, 1);
    return;
}

void DeleteAirplane::on_btnCancel_clicked()
{
    this->close();
}
