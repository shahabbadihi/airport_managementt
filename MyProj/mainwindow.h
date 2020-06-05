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
#include "mymodel.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <QStandardItemModel>

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

    //void updateFlightModel();
    //void print();

private:
    Ui::MainWindow *ui;
    Dialog* addPilotDialog;
    AddHost* addHostDialog;
    deleteHost* deleteHostDialog;
    AddFlightDialog* addFlightDialog;
    AddTicket* addTicketDialog;
    AddAirlineDialog* addAirlineDialog;
    AddAirplaneDialog* addAirplaneDialog;
    AddCarrierDialog* addCarrierDialog;
    DeletePilot* deletePilotDialog;//pilot

    QTimer * timer;

    MyModel<Flight> * model;
};
#endif // MAINWINDOW_H
