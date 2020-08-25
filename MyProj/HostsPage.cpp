#include "HostsPage.h"
#include "ui_HostsPage.h"
#include "Recorder.h"
#include "HostItemModel.h"
#include "Employee.h"
#include "Host.h"
#include <QString>

HostsPage::HostsPage(QWidget *parent) :
    DataMapperPage(HostItemModel::getInstance()
        , parent),
    ui(new Ui::HostsPage)
{
    ui->setupUi(this);

    mapper->setModel(model);
    mapper->addMapping(ui->txtName, 0);
    mapper->addMapping(ui->txtFamily, 1);
    mapper->addMapping(ui->txtNationalCode, 2);
    mapper->addMapping(ui->txtPersonnelCode, 3);
    ui->txtPersonnelCode->setReadOnly(true);

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



    connect(ui->btnNext, SIGNAL(clicked()), this->mapper, SLOT(toNext()));
    connect(ui->btnPre, SIGNAL(clicked()), this->mapper, SLOT(toPrevious()));
}

HostsPage::~HostsPage()
{
    delete ui;
}

void HostsPage::on_btnSubmit_clicked()
{
    this->mapper->submit();
    Recorder<Host>::getInstance()->updateFileAll();
}

void HostsPage::updateButtons(int row)
{
    ui->btnPre->setEnabled(row > 0);
    ui->btnNext->setEnabled(row < model->rowCount() - 1);
}
