#include "deletecarrier.h"
#include "ui_deletecarrier.h"

deleteCarrier::deleteCarrier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteCarrier)
{
    ui->setupUi(this);
}

deleteCarrier::~deleteCarrier()
{
    delete ui;
}
