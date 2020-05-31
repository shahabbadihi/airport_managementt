#include "addairplanedialog.h"
#include "ui_addairplanedialog.h"
#include "Airline.h"
#include "Airplane.h"

template <class T>
Recorder<T>* Recorder<T>::instance;

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
    Airplane * airplane = new Airplane;
    airplane->setAirline(Recorder<Airline>::getInstance()->get_dataList()[ui->comboAirline->currentIndex()]);
    airplane->setSerial(ui->txtSerial->text());
    airplane->setNumOfSeats(ui->spnNumOfSeats->value());

    Recorder<Airplane>::getInstance()->add(airplane);
}

void AddAirplaneDialog::on_btnCancel_clicked()
{
    this->close();
}
