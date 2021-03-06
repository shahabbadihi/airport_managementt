#include "editSeas.h"
#include "ui_editSeas.h"
#include <QLayout>
#include <QRadioButton>
#include "Airplane.h"
#include "attachticket.h"
#include "Seat.h"
editSeas::editSeas(Flight * flight,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editSeas)
{
    this->flight=flight;

    ui->setupUi(this);
    for (int i=0;i<flight->getAirplane()->getcolumnCount();i++){
    ui->seatChart->setHorizontalHeaderItem(i,new QTableWidgetItem(QString::number(i)));
    }
    for (int i=0;i<flight->getAirplane()->getRowCount();i++){
    ui->seatChart->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(i)));
    }

    ui->seatChart->setColumnCount(flight->getAirplane()->getcolumnCount());
    for (int i=0;i<flight->getAirplane()->getRowCount();i++) {
         ui->seatChart->insertRow(ui->seatChart->rowCount());
    }
    update();
}

editSeas::~editSeas()
{
    delete ui;
}

void editSeas::on_pushButton_clicked()
{
    this->close();
}

void editSeas::on_seatChart_cellActivated(int row, int column)
{
    attachTicket * attachTicketDialog=new attachTicket(flight,row,column);
    attachTicketDialog->setModal(true);
   attachTicketDialog->exec();
    delete attachTicketDialog;
}

void editSeas::on_seatChart_cellClicked(int row, int column)
{
    attachTicket * attachTicketDialog=new attachTicket(flight,row,column);
    attachTicketDialog->setModal(true);
    attachTicketDialog->exec();
    delete attachTicketDialog;
    update();
}
void editSeas::update(){
    for (int i=0;i<flight->getAirplane()->getRowCount();i++) {
        for (int j=0;j<flight->getAirplane()->getcolumnCount();j++){
            if(flight->getAirplane()->getSeat(i,j)->isFree(flight)){

            }
            else{
                ui->seatChart->setItem(i,j,new QTableWidgetItem(QString::number(flight->getAirplane()->
                                                                getSeat(i,j)->getTicket(flight)->getNo())));
            }
        }
    }

    emit flight->flightStatusChanged();
}
