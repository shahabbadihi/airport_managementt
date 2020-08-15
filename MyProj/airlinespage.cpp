#include "airlinespage.h"
#include "ui_airlinespage.h"
#include "Recorder.h"
#include "Airline.h"
AirlinesPage::AirlinesPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AirlinesPage),
    airline_item_model(nullptr),
    delegate(nullptr),
    mapper(nullptr)
{
    ui->setupUi(this);
    mapper=new QDataWidgetMapper(this);
    airline_item_model=AirlineItemModel::getInstance();

    mapper->setModel(airline_item_model);
    mapper->addMapping(ui->airlineNameLe,1);
    ui->airlineNameLe->setReadOnly(true);
    mapper->addMapping(ui->CodeLe,2);
   // ui->CodeLe->setReadOnly(true);
    mapper->addMapping(ui->pilotPte,3);
    ui->pilotPte->setReadOnly(true);
    mapper->addMapping(ui->HostPte,4);
    ui->HostPte->setReadOnly(true);
    mapper->addMapping(ui->FlightPte,5);
    ui->FlightPte->setReadOnly(true);
    mapper->addMapping(ui->AirplanePte,6);
    ui->AirplanePte->setReadOnly(true);
    mapper->addMapping(ui->DnFlightPte,7);
    ui->DnFlightPte->setReadOnly(true);
    delegate = new Delegate(this);
    mapper->setItemDelegate(delegate);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->toFirst();

    connect(this->airline_item_model, SIGNAL(rowsAboutToBeRemoved(int)),
            this, SLOT(setCurrentIndex(int)));
    connect(this->airline_item_model, SIGNAL(setIndexWhenRecordAdded()),
            this, SLOT(updateButtonsWhenRecordAdded()));

    connect(this->mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButton(int)));

    connect(ui->prvBtn,SIGNAL(clicked()),mapper,SLOT(toPrevious()));
    connect(ui->nextBtn,SIGNAL(clicked()),mapper,SLOT(toNext()));

}

AirlinesPage::~AirlinesPage()
{
    delete ui;
}
void AirlinesPage::updateButton(int row)
{
    ui->prvBtn->setEnabled(row > 0);
    ui->nextBtn->setEnabled(row < airline_item_model->rowCount() - 1);
}

void AirlinesPage::on_subBtn_clicked()
{
    this->mapper->submit();

}

void AirlinesPage::setCurrentIndex(int row)
{
    if (row == 0)
    {
        this->mapper->revert();
    }
    else
    {
        this->mapper->setCurrentIndex(row - 1);
    }
}

void AirlinesPage::updateButtonsWhenRecordAdded()
{
    this->mapper->toLast();
    this->updateButton(this->airline_item_model->rowCount() - 1);
}

