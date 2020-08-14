#include "dialog.h"
#include "ui_dialog.h"
#include "Pilot.h"
#include "pd1.h"
#include "pd2.h"
#include "pd3.h"
#include "Recorder.h"
#include <QMessageBox>
#include <QVector>
#include <Airline.h>
#include <stdexcept>
using namespace std;

//template <class T>
//QVector<T*> Recorder<T>::dataList;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    foreach (Airline* a, Recorder<Airline>::getInstance()->get_dataList())
    {
        ui->comboAirline->addItem(a->getName());
    }
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
    try
    {
        Pilot* pilot = nullptr;
        QRadioButton* radio1 = ui->radio1;
        QRadioButton* radio2 = ui->radio2;
        QRadioButton* radio3 = ui->radio3;

        if (radio1->isChecked())
            pilot = new PD1;
        else if (radio2->isChecked())
            pilot = new PD2;
        else if (radio3->isChecked())
            pilot = new PD3;


        pilot->set_personnelCode(ui->txtPersonnelCode->text().toLongLong());
        pilot->setAirline(Recorder<Airline>::getInstance()->get_dataList()[ui->comboAirline->currentIndex()]);
        pilot->set_fname(ui->txtFname->text());
        pilot->set_lname(ui->txtLname->text());
        pilot->set_birthDate(ui->dtBirthDate->date());
        pilot->set_employmentDate(ui->dtEmploymentDate->date());
        pilot->set_nationalCode(ui->txtNationalCode->text().toLongLong());




        //Recorder<Pilot>::record(pilot);
        //Recorder<Pilot>::addToFile(pilot);
        //pilot->get_recorder().addToFile(pilot);
        Recorder<Pilot>::getInstance()->add(pilot);

        QMessageBox msg;
        msg.setText("Submit Successfully!");
        msg.exec();

        Recorder<Pilot>::getInstance()->print_dataList();
        //delete pilot;
    }

    catch (invalid_argument e)
    {
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }
}
