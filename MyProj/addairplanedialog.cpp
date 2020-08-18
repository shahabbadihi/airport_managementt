#include "addairplanedialog.h"
#include "ui_addairplanedialog.h"
#include "Airline.h"
#include "Airplane.h"
#include <stdexcept>
using namespace std;

AddAirplaneDialog::AddAirplaneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAirplaneDialog)
{
    ui->setupUi(this);

    foreach (Airline* a, Recorder<Airline>::getInstance()->get_dataList())
    {
        ui->comboAirline->addItem(a->getName());
    }
}

AddAirplaneDialog::~AddAirplaneDialog()
{
    delete ui;
}

void AddAirplaneDialog::on_btnSubmit_clicked()
{
//    Airplane * airplane = new Airplane;
//    airplane->setSerial(ui->txtSerial->text());
//    airplane->setAirline(Recorder<Airline>::getInstance()->get_dataList()[ui->comboAirline->currentIndex()]);

//    airplane->setNumOfSeats(ui->spnNumOfSeats->value());
    Airplane * airplane = nullptr;
    try
    {
        airplane = new Airplane(ui->txtSerial->text(),
                                           Recorder<Airline>::getInstance()->get_dataList()[ui->comboAirline->currentIndex()],
                ui->spnNumOfRows->value(), ui->spnNumOfCols->value());

        Recorder<Airplane>::getInstance()->add(airplane);

        QMessageBox msg;
        msg.setText("Submit Successfully!");
        msg.exec();
    }

    catch (invalid_argument e)
    {
        delete airplane;
        airplane = nullptr;
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }
}

void AddAirplaneDialog::on_btnCancel_clicked()
{
    this->close();
}
