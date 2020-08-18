#include "HostsPage.h"
#include "ui_HostsPage.h"
#include "Recorder.h"
#include "HostItemModel.h"
#include "Employee.h"
#include "Host.h"
#include <QString>

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
    ui->dtBirthDate->setReadOnly(true);
    mapper->addMapping(ui->dtEmploymentDate, 6);
    ui->dtEmploymentDate->setReadOnly(true);

    mapper->addMapping(ui->plainFlights, 7);
    ui->plainFlights->setReadOnly(true);

    mapper->addMapping(ui->plainDoneFlights, 8);
    ui->plainDoneFlights->setReadOnly(true);

    mapper->addMapping(ui->wage_of_host, 9);
    ui->wage_of_host->setReadOnly(true);


    delegate = new Delegate(this);
    mapper->setItemDelegate(delegate);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->toFirst();

    connect(this->host_item_model, SIGNAL(rowsAboutToBeRemoved(int)),
            this, SLOT(setCurrentIndex(int)));
    connect(this->host_item_model, SIGNAL(setIndexWhenRecordAdded()),
            this, SLOT(updateButtonsWhenRecordAdded()));

    connect(this->mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));

    connect(ui->btnNext, SIGNAL(clicked()), this->mapper, SLOT(toNext()));
    connect(ui->btnPre, SIGNAL(clicked()), this->mapper, SLOT(toPrevious()));
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
    Recorder<Host>::getInstance()->updateFileAll();
}

void HostsPage::updateButtons(int row)
{
    ui->btnPre->setEnabled(row > 0);
    ui->btnNext->setEnabled(row < host_item_model->rowCount() - 1);
}

void HostsPage::setCurrentIndex(int row)
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

void HostsPage::updateButtonsWhenRecordAdded()
{
    this->mapper->toLast();
    this->updateButtons(this->host_item_model->rowCount() - 1);
}
