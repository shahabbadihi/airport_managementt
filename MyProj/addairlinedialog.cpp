#include "addairlinedialog.h"
#include "ui_addairlinedialog.h"
#include "Airline.h"
#include "Recorder.h"

template <class T>
QVector<T*> Recorder<T>::dataList;

AddAirlineDialog::AddAirlineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAirlineDialog)
{
    ui->setupUi(this);
}

AddAirlineDialog::~AddAirlineDialog()
{
    delete ui;
}

void AddAirlineDialog::on_btnSubmit_clicked()
{
    Airline* airline = new Airline(ui->txtName->text(), ui->txtCode->text());


    Recorder<Airline>::add(airline);
}

void AddAirlineDialog::on_btnCancel_clicked()
{
    this->close();
}
