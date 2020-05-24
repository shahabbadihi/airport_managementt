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
QVector<T*> Recorder<T>::dataList;

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
    Host * h = Recorder<Host>::searchByCode(ui->txtPersonnelCode->text());
    if(h){
        if(h->getFname()==ui->txtFname->text() && h->getLname()==ui->txtLname->text()){
           Recorder<Host>::removeFromFile(h);
           Recorder<Host>::remove(h);
           //
           //
           QMessageBox msg;
           msg.setText("Delete Successfully!");
           msg.exec();
           qDebug() << "List of hosts after delete:";
           Recorder<Host>::print_dataList();
        }
    }
}


