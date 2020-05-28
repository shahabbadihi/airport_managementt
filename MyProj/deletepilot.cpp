#include "deletepilot.h"
#include "ui_deletepilot.h"
#include "Pilot.h"
#include <QVector>
#include "Recorder.h"

template <class T>
QVector<T*> Recorder<T>::dataList;

DeletePilot::DeletePilot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeletePilot)
{
    ui->setupUi(this);
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
    Pilot * h = Recorder<Pilot>::searchByCode(ui->PersonnelCodeTxt->text());
    if(h){
        if(h->getFname()==ui->FnameTxt->text() && h->getLname()==ui->LnameTxt->text()){

           //Recorder<Pilot>::removeFromFile(h);
           Recorder<Pilot>::remove(h);
           //
           //
           QMessageBox msg;
           msg.setText("Delete Successfully!");
           msg.exec();
           qDebug() << "List of pilots after delete:";
           Recorder<Pilot>::print_dataList();
        }
    }
}
