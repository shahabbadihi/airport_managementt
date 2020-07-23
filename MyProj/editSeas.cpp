#include "editSeas.h"
#include "ui_editSeas.h"
#include <QLayout>
#include <QRadioButton>
#include "Airplane.h"
editSeas::editSeas(Flight * flight,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editSeas)
{
    this->flight=flight;
    ui->seatChart->setColumnCount(flight->getAirplane()->getcolumnCount());
    for (int i=0;i<flight->getAirplane()->getRowCount();i++) {
      ui->seatChart->insertRow(ui->seatChart->rowCount());
    }

    ui->setupUi(this);
}

editSeas::~editSeas()
{
    delete ui;
}

void editSeas::on_pushButton_clicked()
{

}
