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
    Host * host = nullptr;
    try
    {
        qlonglong p_code = ui->txtPersonnelCode->text().toLongLong();
        Airline * airline = Recorder<Airline>::getInstance()->get_dataList()[ui->comboAirline->currentIndex()];
        QString fname = ui->txtFname->text();
        QString lname = ui->txtLname->text();
        QDate b_date = ui->dtBirthDate->date();
        QDate e_date = ui->dtEmploymentDate->date();
        qlonglong n_code = ui->txtNationalCode->text().toLongLong();

        host = new Host(p_code, airline, fname, lname, b_date,
                              e_date, n_code);

        Recorder<Host>::getInstance()->add(host);

        QMessageBox msg;
        msg.setText("Submit Successfully!");
        msg.exec();

        Recorder<Host>::getInstance()->print_dataList();
    }

    catch (invalid_argument e)
    {
        delete host;
        host = nullptr;
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }
}
