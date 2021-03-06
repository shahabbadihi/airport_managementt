#ifndef FLIGHTTABLEPAGE_H
#define FLIGHTTABLEPAGE_H

#include <QWidget>
#include "flighttablemodel.h"
#include <QPushButton>
#include <QSignalMapper>
#include <QTimer>
#include <QSortFilterProxyModel>

namespace Ui {
class FlightTablePage;
}

class FlightTablePage : public QWidget
{
    Q_OBJECT

public:
    explicit FlightTablePage(QWidget *parent = nullptr);
    ~FlightTablePage();

public slots:
    void showClock();
    void addButtonFlightTable(int row);
    void removeButtonFlightTable(int row);
    void showDelayDialog(int row);
    void showStatusDialog(int row);
    void showDetailsDialog(int row);
private:
    Ui::FlightTablePage *ui;

    QTimer * timer;

    FlightTableModel * flight_table_model;

    QVector<QPushButton*> delay_buttons;
    QVector<QPushButton*> status_buttons;
    QVector<QPushButton*> details_buttons;

    QSignalMapper * signal_mapper_delay;
    QSignalMapper * signal_mapper_status;
    QSignalMapper * signal_mapper_details;

    QSortFilterProxyModel * proxy;
};

#endif // FLIGHTTABLEPAGE_H
