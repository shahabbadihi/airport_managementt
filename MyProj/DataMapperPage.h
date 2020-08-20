#ifndef DATAMAPPERPAGE_H
#define DATAMAPPERPAGE_H

#include <QObject>
#include <QWidget>
#include "MyAbstractItemModel.h"
#include "flighttablemodel.h"
#include "delegate.h"
#include <QDataWidgetMapper>

class DataMapperPage : public QWidget
{
    Q_OBJECT
public:
    explicit DataMapperPage(MyAbstractItemModel * m,
                               QWidget *parent = nullptr);

private slots:
    virtual void updateButtons(int row) = 0;
    void setCurrentIndex(int row);
    void updateButtonsWhenRecordAdded();
    void connectFlightToMapper(int);
    void Update();
protected:
    MyAbstractItemModel * model;
    FlightTableModel * flight_table_model;
    Delegate * delegate;
    QDataWidgetMapper * mapper;
};

#endif // DATAMAPPERPAGE_H
