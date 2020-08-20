#include "DataMapperPage.h"


DataMapperPage::DataMapperPage(MyAbstractItemModel *m
                               , QWidget *parent)
    : QWidget(parent)
{
    model = m;
    mapper = new QDataWidgetMapper(this);

    connect(this->model, SIGNAL(rowsAboutToBeRemoved(int)),
            this, SLOT(setCurrentIndex(int)));
    connect(this->model, SIGNAL(setIndexWhenRecordAdded()),
            this, SLOT(updateButtonsWhenRecordAdded()));

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

