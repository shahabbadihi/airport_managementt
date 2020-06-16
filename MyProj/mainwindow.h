#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include "addhost.h"
#include "deletehost.h"
#include "addflightdialog.h"
#include "addticket.h"
#include "addairlinedialog.h"
#include "addairplanedialog.h"
#include "addcarrierdialog.h"
#include "deletepilot.h"

//#include "mymodel.h"
#include "flighttablemodel.h"
#include "pilotitemmodel.h"
#include "mydelegate.h"
#include "deleteflight.h"
#include "deletecarrier.h"

//#include "mymodel.h"
#include "flighttablemodel.h"
#include "pilotitemmodel.h"

#include "deleteflight.h"
#include "deletecarrier.h"
#include "deleteticket.h"

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include <QSignalMapper>

class Flight;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//signals:
//    void updateFlightModel();
private slots:

    void on_actionAddPilot_triggered();

    void on_actionAdd_Host_triggered();

    //void on_actionhost_triggered();

    void on_actionDeleteHost_triggered();

    void on_actionAddFlight_triggered();


    void on_actionAddTicket_triggered();

    void on_actionAddAirline_triggered();

    void on_actionAddAirplane_triggered();

//    void on_actionPilot_triggered();

    void on_actionDeletePilot_triggered();

    void on_actionAddCarrier_triggered();

    void updateFiles();

    void showClock();

    void updateFlightState();

    void updateButtonsPilot(int);

    void addButtonFlightTable(int);
    void removeButtonFlightTable(int);
    void showDelayDialog(int);

    void showStatusDialog(int);

    //void updateFlightModel();
    //void print();

    void on_actionFlight_triggered();

    void on_actioncarrier_triggered();

    void on_actionTicket_triggered();

private:
    Ui::MainWindow *ui;
    Dialog* addPilotDialog;
    AddHost* addHostDialog;

    AddFlightDialog* addFlightDialog;
    AddTicket* addTicketDialog;
    AddAirlineDialog* addAirlineDialog;
    AddAirplaneDialog* addAirplaneDialog;
    AddCarrierDialog* addCarrierDialog;
    DeletePilot* deletePilotDialog;//pilot
    deleteHost* deleteHostDialog;
    deleteFlight* deleteFlightDialog;
    deleteCarrier* deleteCarrierDialog;
    deleteTicket * deleteTicketDialog;
    QTimer * timer;

    FlightTableModel * flight_table_model;
    //MyDelegate * delegate;
    QVector<QPushButton*> delay_buttons;
    QVector<QPushButton*> status_buttons;
    QSignalMapper * signal_mapper_delay;
    QSignalMapper * signal_mapper_status;

    PilotItemModel * pilot_item_model;
    QDataWidgetMapper * pilot_mapper;
};
#endif // MAINWINDOW_H
