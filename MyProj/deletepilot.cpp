#include "deletepilot.h"
#include "ui_deletepilot.h"
#include "Pilot.h"
#include "pilotlistmodel.h"
#include <QVector>
#include "Recorder.h"

DeletePilot::DeletePilot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeletePilot)
{
    ui->setupUi(this);

    this->model = PilotListModel::getInstance();
    ui->listView->setModel(model);
}

DeletePilot::~DeletePilot()
{
    delete ui;
}

void DeletePilot::on_pushButton_2_clicked()
{
    this->close();
}

void DeletePilot::on_pushButton_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    this->model->removeRows(index.row(), 1);
    //
    //
    QMessageBox msg;
    msg.setText("Delete Successfully!");
    msg.exec();
    qDebug() << "List of pilots after delete:";
    Recorder<Pilot>::getInstance()->print_dataList();
}
