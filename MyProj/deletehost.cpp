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
    Host * h = Recorder<Host>::searchPersonnelCode(ui->txtPersonnelCode->text().toLong());
    if(h){
        if(h->get_name()==ui->txtFname->text() && h->get_family()==ui->txtLname->text()){
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


