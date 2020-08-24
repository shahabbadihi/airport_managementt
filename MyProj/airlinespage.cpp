#include "airlinespage.h"
#include "ui_airlinespage.h"
#include "Recorder.h"
#include "Airline.h"
AirlinesPage::AirlinesPage(QWidget *parent) :
    DataMapperPage(AirlineItemModel::getInstance()
        , parent),
    ui(new Ui::AirlinesPage)
{
    ui->setupUi(this);

    mapper->setModel(model);
    mapper->addMapping(ui->airlineNameLe,0);
    ui->airlineNameLe->setReadOnly(true);
    mapper->addMapping(ui->CodeLe,1);
    mapper->addMapping(ui->pilotPte,2);
    ui->pilotPte->setReadOnly(true);
    mapper->addMapping(ui->HostPte,3);
    ui->HostPte->setReadOnly(true);
    mapper->addMapping(ui->FlightPte,4);
    ui->FlightPte->setReadOnly(true);
    mapper->addMapping(ui->AirplanePte,5);
    ui->AirplanePte->setReadOnly(true);
    delegate = new Delegate(this);
    mapper->setItemDelegate(delegate);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->toFirst();


    connect(ui->prvBtn,SIGNAL(clicked()),mapper,SLOT(toPrevious()));
    connect(ui->nextBtn,SIGNAL(clicked()),mapper,SLOT(toNext()));

}

AirlinesPage::~AirlinesPage()
{
    delete ui;
}
void AirlinesPage::updateButtons(int row)
{
    ui->prvBtn->setEnabled(row > 0);
    ui->nextBtn->setEnabled(row < model->rowCount() - 1);
}

void AirlinesPage::on_subBtn_clicked()
{
    this->mapper->submit();
    Recorder<Airline>::getInstance()->updateFileAll();
}
