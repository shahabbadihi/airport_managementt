#include "pilotspage.h"
#include "ui_pilotspage.h"

PilotsPage::PilotsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PilotsPage),
    pilot_item_model(nullptr),
    delegate(nullptr),
    mapper(nullptr)
{
    ui->setupUi(this);

    this->mapper = new QDataWidgetMapper(this);
    this->pilot_item_model = PilotItemModel::getInstance();
    mapper->setModel(pilot_item_model);
    mapper->addMapping(ui->txtNamePilot, 0);
    mapper->addMapping(ui->txtFamilyPilot, 1);
    mapper->addMapping(ui->txtNationalCodePilot, 2);
    mapper->addMapping(ui->txtPersonnelCodePilot, 3);
    mapper->addMapping(ui->txtAirlinePilot, 4);
    ui->txtAirlinePilot->setReadOnly(true);
    mapper->addMapping(ui->dtBirthDatePliot, 5);
    mapper->addMapping(ui->dtEmploymentDatePilot, 6);
    mapper->addMapping(ui->plainFlights, 7);
    ui->plainFlights->setReadOnly(true);

    mapper->addMapping(ui->plainDoneFlights, 8);
    ui->plainDoneFlights->setReadOnly(true);

    mapper->addMapping(ui->txtDegreePilot, 9);
    ui->txtDegreePilot->setReadOnly(true);

    delegate = new Delegate(this);
    mapper->setItemDelegate(delegate);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->toFirst();

    connect(this->mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));

    connect(ui->btnNextPilot, SIGNAL(clicked()), this->mapper, SLOT(toNext()));
    connect(ui->btnPrePilot, SIGNAL(clicked()), this->mapper, SLOT(toPrevious()));
}

PilotsPage::~PilotsPage()
{
    delete ui;
    delete delegate;
    delete mapper;
}

void PilotsPage::on_btnSubmit_clicked()
{
    this->mapper->submit();
}

void PilotsPage::updateButtons(int row)
{
    ui->btnPrePilot->setEnabled(row > 0);
    ui->btnNextPilot->setEnabled(row < pilot_item_model->rowCount() - 1);
}
