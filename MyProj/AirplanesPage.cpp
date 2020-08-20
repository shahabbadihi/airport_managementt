#include "AirplanesPage.h"
#include "ui_AirplanesPage.h"
#include "Recorder.h"
#include "Airplane.h"

AirplanesPage::AirplanesPage(QWidget *parent) :
    DataMapperPage(AirplaneItemModel::getInstance()
        , parent),
    ui(new Ui::AirplanesPage)
{
    ui->setupUi(this);

//    this->mapper = new QDataWidgetMapper(this);
//    this->model = AirplaneItemModel::getInstance();
    mapper->setModel(model);
    mapper->addMapping(ui->txtSerial, 0);
    mapper->addMapping(ui->txtNumOfRows, 1);
    ui->txtNumOfRows->setReadOnly(true);
    mapper->addMapping(ui->txtNumOfCols, 2);
    ui->txtNumOfCols->setReadOnly(true);
    mapper->addMapping(ui->txtAirline, 3);
    ui->txtAirline->setReadOnly(true);
    mapper->addMapping(ui->plainFlights, 4);
    ui->plainFlights->setReadOnly(true);

    delegate = new Delegate(this);
    mapper->setItemDelegate(delegate);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->toFirst();

//    connect(this->airplane_item_model, SIGNAL(rowsAboutToBeRemoved(int)),
//            this, SLOT(setCurrentIndex(int)));
//    connect(this->airplane_item_model, SIGNAL(setIndexWhenRecordAdded()),
//            this, SLOT(updateButtonsWhenRecordAdded()));

//    connect(this->mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));

    connect(ui->btnNext, SIGNAL(clicked()), this->mapper, SLOT(toNext()));
    connect(ui->btnPre, SIGNAL(clicked()), this->mapper, SLOT(toPrevious()));
}

AirplanesPage::~AirplanesPage()
{
    delete ui;
}

void AirplanesPage::on_btnSubmit_clicked()
{
    this->mapper->submit();
    Recorder<Airplane>::getInstance()->updateFileAll();
}

void AirplanesPage::updateButtons(int row)
{
    ui->btnPre->setEnabled(row > 0);
    ui->btnNext->setEnabled(row < model->rowCount() - 1);
}

//void AirplanesPage::setCurrentIndex(int row)
//{
//    if (row == 0)
//    {
//        this->mapper->revert();
//    }
//    else
//    {
//        this->mapper->setCurrentIndex(row - 1);
//    }
//}

//void AirplanesPage::updateButtonsWhenRecordAdded()
//{
//    this->mapper->toLast();
//    this->updateButtons(this->airplane_item_model->rowCount() - 1);
//}
