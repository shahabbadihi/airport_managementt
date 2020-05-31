#include "deletehost.h"
#include "ui_deletehost.h"
#include <QVector>
#include "Recorder.h"
#include "Host.h"
#include <iostream>
#include <QString>
#include <string>


#include <QMessageBox>
template <class T>
Recorder<T>* Recorder<T>::instance;

deleteHost::deleteHost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteHost)
{
    ui->setupUi(this);
}

deleteHost::~deleteHost()
{
    delete ui;
}

void deleteHost::on_pushButton_2_clicked()
{
    this->close();
}

void deleteHost::on_pushButton_clicked()
{
    Host * h = Recorder<Host>::getInstance()->searchByCode(ui->txtPersonnelCode->text());
    if(h){
        if(h->getFname()==ui->txtFname->text() && h->getLname()==ui->txtLname->text()){

           //Recorder<Host>::removeFromFile(h);
           //Recorder<Host>::removeFromFile(h);
           Recorder<Host>::getInstance()->remove(h);
           //
           //
           QMessageBox msg;
           msg.setText("Delete Successfully!");
           msg.exec();
           qDebug() << "List of hosts after delete:";
           Recorder<Host>::getInstance()->print_dataList();
           Recorder<Flight>::getInstance()->print_dataList();
        }
    }
}


