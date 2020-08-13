#include "AirplanesPage.h"
#include "ui_AirplanesPage.h"

AirplanesPage::AirplanesPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AirplanesPage),
    airplane_item_model(nullptr),
    delegate(nullptr),
    mapper(nullptr)
{
    ui->setupUi(this);

    this->mapper = new QDataWidgetMapper(this);
    this->airplane_item_model = AirplaneItemModel::getInstance();
    mapper->setModel(airplane_item_model);
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

    connect(this->airplane_item_model, SIGNAL(modelReset()), this->mapper, SLOT(toFirst()));
    connect(this->mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));

    connect(ui->btnNext, SIGNAL(clicked()), this->mapper, SLOT(toNext()));
    connect(ui->btnPre, SIGNAL(clicked()), this->mapper, SLOT(toPrevious()));
}

AirplanesPage::~AirplanesPage()
{
    delete ui;
    delete delegate;
    delete mapper;
}

void AirplanesPage::on_btnSubmit_clicked()
{
    this->mapper->submit();
}

void AirplanesPage::updateButtons(int row)
{
    ui->btnPre->setEnabled(row > 0);
    ui->btnNext->setEnabled(row < airplane_item_model->rowCount() - 1);
}
