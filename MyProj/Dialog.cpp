#include "dialog.h"
#include "ui_dialog.h"
#include "Pilot.h"
#include "Recorder.h"
#include <QMessageBox>
#include <QVector>

template <class T>
QVector<T*> Recorder<T>::dataList;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    this->close();
    //this->~Dialog();
}

void Dialog::on_pushButton_clicked()
{
    Pilot* pilot = new Pilot();

    pilot->set_fname(ui->txtFname->text());
    pilot->set_lname(ui->txtLname->text());
    pilot->set_birthDate(ui->dtBirthDate->date());
    pilot->set_employmentDate(ui->dtEmploymentDate->date());
    pilot->set_nationalCode(ui->txtNationalCode->text().toLong());
    pilot->set_personnelCode(ui->txtPersonnelCode->text().toLong());

    QRadioButton* radio1 = ui->radio1;
    QRadioButton* radio2 = ui->radio2;
    QRadioButton* radio3 = ui->radio3;

    if (radio1->isChecked())
        pilot->set_degree(radio1->text().toInt());
    else if (radio2->isChecked())
        pilot->set_degree(radio2->text().toInt());
    else if (radio3->isChecked())
        pilot->set_degree(radio3->text().toInt());

    //Recorder<Pilot>::record(pilot);
    //Recorder<Pilot>::addToFile(pilot);
    //pilot->get_recorder().addToFile(pilot);
    Recorder<Pilot>::add(pilot);

    QMessageBox msg;
    msg.setText("Submit Successfully!");
    msg.exec();

    Recorder<Pilot>::print_dataList();
    //delete pilot;
}
