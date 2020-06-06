#include "deleteflight.h"
#include "ui_deleteflight.h"

deleteFlight::deleteFlight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteFlight)
{
    ui->setupUi(this);
}

deleteFlight::~deleteFlight()
{
    delete ui;
}
