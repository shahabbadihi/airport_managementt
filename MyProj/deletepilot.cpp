#include "deletepilot.h"
#include "ui_deletepilot.h"
#include "Pilot.h"
#include <QVector>
#include "Recorder.h"
deleteEmp::deleteEmp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteEmp)
{
    ui->setupUi(this);
}

deleteEmp::~deleteEmp()
{
    delete ui;
}

void deleteEmp::on_pushButton_2_clicked()
{
    this->close();
}

void deleteEmp::on_pushButton_clicked()
{
    Pilot * h = Recorder<Pilot>::searchPersonnelCode(ui->PersonnelCodeTxt->text().toLong());
    if(h){
        if(h->getFname()==ui->FnameTxt->text() && h->getLname()==ui->LnameTxt->text()){

           Recorder<Pilot>::removeFromFile(h);
           Recorder<Pilot>::remove(h);
           //
           //
           QMessageBox msg;
           msg.setText("Delete Successfully!");
           msg.exec();
           qDebug() << "List of hosts after delete:";
           Recorder<Pilot>::print_dataList();
        }
    }
}
