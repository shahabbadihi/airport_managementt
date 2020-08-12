#include "HostsPage.h"
#include "ui_HostsPage.h"

HostsPage::HostsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HostsPage),
    host_item_model(nullptr),
    delegate(nullptr),
    mapper(nullptr)
{
    ui->setupUi(this);

    this->mapper = new QDataWidgetMapper(this);
    this->host_item_model = HostItemModel::getInstance();
    mapper->setModel(host_item_model);
    mapper->addMapping(ui->txtName, 0);
    mapper->addMapping(ui->txtFamily, 1);
    mapper->addMapping(ui->txtNationalCode, 2);
    mapper->addMapping(ui->txtPersonnelCode, 3);
    mapper->addMapping(ui->txtAirline, 4);
    ui->txtAirline->setReadOnly(true);
    mapper->addMapping(ui->dtBirthDate, 5);
    mapper->addMapping(ui->dtEmploymentDate, 6);
    mapper->addMapping(ui->plainFlights, 7);
    ui->plainFlights->setReadOnly(true);

    mapper->addMapping(ui->plainDoneFlights, 8);
    ui->plainDoneFlights->setReadOnly(true);


    delegate = new Delegate(this);
    mapper->setItemDelegate(delegate);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->toFirst();

    connect(this->mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));

    connect(ui->btnNextPilot, SIGNAL(clicked()), this->mapper, SLOT(toNext()));
    connect(ui->btnPrePilot, SIGNAL(clicked()), this->mapper, SLOT(toPrevious()));
}

HostsPage::~HostsPage()
{
    delete ui;
    delete delegate;
    delete mapper;
}

void HostsPage::on_btnSubmit_clicked()
{
    this->mapper->submit();
}

void HostsPage::updateButtons(int row)
{
    ui->btnPrePilot->setEnabled(row > 0);
    ui->btnNextPilot->setEnabled(row < host_item_model->rowCount() - 1);
}
