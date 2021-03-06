#include "pilotspage.h"
#include "ui_pilotspage.h"
#include <QThread>
#include "ThreadedJob.h"
#include "Recorder.h"
#include "pilotitemmodel.h"
#include "Employee.h"
#include "Pilot.h"
#include <QString>

PilotsPage::PilotsPage(QWidget *parent) :
    DataMapperPage(PilotItemModel::getInstance(),
                   parent),
    ui(new Ui::PilotsPage)
{
    ui->setupUi(this);

    mapper->setModel(model);
    mapper->addMapping(ui->txtNamePilot, 0);
    mapper->addMapping(ui->txtFamilyPilot, 1);
    mapper->addMapping(ui->txtNationalCodePilot, 2);
    mapper->addMapping(ui->txtPersonnelCodePilot, 3);
    ui->txtPersonnelCodePilot->setReadOnly(true);
    mapper->addMapping(ui->txtAirlinePilot, 4);
    ui->txtAirlinePilot->setReadOnly(true);
    mapper->addMapping(ui->dtBirthDatePliot, 5);
    ui->dtBirthDatePliot->setReadOnly(true);
    mapper->addMapping(ui->dtEmploymentDatePilot, 6);
    ui->dtEmploymentDatePilot->setReadOnly(true);
    mapper->addMapping(ui->plainFlights, 7);
    ui->plainFlights->setReadOnly(true);

    mapper->addMapping(ui->plainDoneFlights, 8);
    ui->plainDoneFlights->setReadOnly(true);

    mapper->addMapping(ui->txtDegreePilot, 9);
    ui->txtDegreePilot->setReadOnly(true);

    mapper->addMapping(ui->wage_of_pilot, 10);
    ui->wage_of_pilot->setReadOnly(true);

    delegate = new Delegate(this);
    mapper->setItemDelegate(delegate);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->toFirst();


    connect(ui->btnNextPilot, SIGNAL(clicked()), this->mapper, SLOT(toNext()));
    connect(ui->btnPrePilot, SIGNAL(clicked()), this->mapper, SLOT(toPrevious()));
}

PilotsPage::~PilotsPage()
{
    delete ui;
}

void PilotsPage::on_btnSubmit_clicked()
{
    this->mapper->submit();
    Recorder<Pilot>::getInstance()->updateFileAll();
}

void PilotsPage::updateButtons(int row)
{
    ui->btnPrePilot->setEnabled(row > 0);
    ui->btnNextPilot->setEnabled(row < model->rowCount() - 1);
}
