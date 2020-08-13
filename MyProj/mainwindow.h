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
#include "DeleteAirplane.h"

#include "flighttablemodel.h"
#include "delegate.h"
#include "deleteflight.h"
#include "deletecarrier.h"

#include "pilotitemmodel.h"

#include "deleteflight.h"
#include "deletecarrier.h"
#include "deleteticket.h"

#include <QMainWindow>
#include <QTimer>
#include <QTabWidget>


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

    //void updateFiles();
    //void updateFlightModel();
    //void print();

    void on_actionFlight_triggered();

    void on_actioncarrier_triggered();

    void on_actionTicket_triggered();

    void on_actionairplane_triggered();

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
    DeleteAirplane * deleteAirplaneDialog;

    //QTimer * timer;

    QTabWidget * tab_widget;

};
#endif // MAINWINDOW_H
