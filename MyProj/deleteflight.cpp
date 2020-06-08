#include "deleteflight.h"
#include "ui_deleteflight.h"
#include "Flight.h"

deleteFlight::deleteFlight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteFlight)
{
    ui->setupUi(this);

    this->model = FlightListModel::getInstance();
    ui->listView->setModel(model);
}

deleteFlight::~deleteFlight()
{
    delete ui;
}

void deleteFlight::on_pushButton_2_clicked()
{
//    Flight * f = Recorder<Flight>::getInstance()->searchByCode(ui->flightsSerialTxt->text());
//    if(f){
//        if(f->getSource()==ui->flightSourceTxt->text() && f->getDestination()==ui->flightDestinationTxt->text()){
//           Recorder<Flight>::getInstance()->remove(f);
            QModelIndex index = ui->listView->currentIndex();
            this->model->removeRows(index.row(), 1);
           QMessageBox msg;
           msg.setText("Delete Successfully!");
           msg.exec();
           qDebug() << "List of flights after delete:";
           Recorder<Flight>::getInstance()->print_dataList();
//        }
//    }
}

void deleteFlight::on_pushButton_clicked()
{
    this->close();
}
