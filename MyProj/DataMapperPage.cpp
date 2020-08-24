#include "DataMapperPage.h"
#include "Recorder.h"
#include "Flight.h"


DataMapperPage::DataMapperPage(MyAbstractItemModel *m
                               , QWidget *parent)
    : QWidget(parent)
{
    model = m;
    mapper = new QDataWidgetMapper(this);
    flight_table_model = FlightTableModel::getInstance();

    connect(this->model, SIGNAL(rowsAboutToBeRemoved(int)),
            this, SLOT(setCurrentIndex(int)));
    connect(this->model, SIGNAL(setIndexWhenRecordAdded()),
            this, SLOT(updateButtonsWhenRecordAdded()));

    foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
    {
        connect(f, SIGNAL(flightStatusChanged()), this, SLOT(Update()));
    }

    connect(flight_table_model, SIGNAL(recordInsertedSignal(int)), this, SLOT(connectFlightToMapper(int)));

    connect(this->mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
}

void DataMapperPage::setCurrentIndex(int row)
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

void DataMapperPage::updateButtonsWhenRecordAdded()
{
    this->mapper->toLast();
    this->updateButtons(this->model->rowCount() - 1);
}

void DataMapperPage::connectFlightToMapper(int r)
{
    connect(Recorder<Flight>::getInstance()->get_dataList()[r],
            SIGNAL(flightStatusChanged()), this,
            SLOT(Update()));
}

void DataMapperPage::Update()
{
    int index = this->mapper->currentIndex();
    this->mapper->toFirst();
    this->mapper->setCurrentIndex(index);
}

