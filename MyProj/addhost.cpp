#include "addhost.h"
#include "ui_addHost.h"
#include <QString>
#include <QMessageBox>
#include <QVector>
#include "Host.h"
#include "Recorder.h"
#include "Airline.h"
#include <stdexcept>
using namespace std;

AddHost::AddHost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddHost)
{
    ui->setupUi(this);

    foreach (Airline* a, Recorder<Airline>::getInstance()->get_dataList())
    {
        ui->comboAirline->addItem(a->getName());
    }
}

AddHost::~AddHost()
{
    delete ui;
}

void AddHost::on_pushButton_2_clicked()
{
    this->close();
}

void AddHost::on_pushButton_clicked()
{
    try
    {
        Host* host = new Host();
        host->set_personnelCode(ui->txtPersonnelCode->text().toLongLong());
        host->setAirline(Recorder<Airline>::getInstance()->get_dataList()[ui->comboAirline->currentIndex()]);
        host->set_fname(ui->txtFname->text());
        host->set_lname(ui->txtLname->text());
        host->set_birthDate(ui->dtBirthDate->date());
        host->set_employmentDate(ui->dtEmploymentDate->date());
        host->set_nationalCode(ui->txtNationalCode->text().toLongLong());


        //Recorder<Host>::record(host);
        //Recorder<Host>::addToFile(host);
        //pilot->get_recorder().addToFile(pilot);
        Recorder<Host>::getInstance()->add(host);

        QMessageBox msg;
        msg.setText("Submit Successfully!");
        msg.exec();

        Recorder<Host>::getInstance()->print_dataList();
    }

    catch (invalid_argument e)
    {
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }
}
