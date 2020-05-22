#include "buyticketdialog.h"
#include "ui_buyticketdialog.h"

BuyTicketDialog::BuyTicketDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyTicketDialog)
{
    ui->setupUi(this);
}

BuyTicketDialog::~BuyTicketDialog()
{
    delete ui;
}
