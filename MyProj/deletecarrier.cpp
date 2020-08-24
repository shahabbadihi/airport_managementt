#include "deletecarrier.h"
#include "ui_deletecarrier.h"
#include "Carrier.h"

deleteCarrier::deleteCarrier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteCarrier)
{
    ui->setupUi(this);
}

deleteCarrier::~deleteCarrier()
{
    delete ui;
}

void deleteCarrier::on_btnCancel_clicked()
{
    this->close();
}

void deleteCarrier::on_btnSubmit_clicked()
{
    Carrier * c = Recorder<Carrier>::getInstance()->searchByCode(ui->txtSerial->text());
    if(c){
        if(c->getPlace()==ui->txtPlace->text() ){

           Recorder<Carrier>::getInstance()->remove(c);
           //
           //
           QMessageBox msg;
           msg.setText("Delete Successfully!");
           msg.exec();
           qDebug() << "List of carriers after delete:";
           Recorder<Carrier>::getInstance()->print_dataList();
        }
    }
}
