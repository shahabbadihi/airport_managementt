#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include "addhost.h"
#include "deletehost.h"
#include "addflightdialog.h"
#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionAddPilot_triggered();

    void on_actionAdd_Host_triggered();

    //void on_actionhost_triggered();

    void on_actionDeleteHost_triggered();

    void on_actionAddFlight_triggered();


private:
    Ui::MainWindow *ui;
    Dialog* addPilotDialog;
    AddHost* addHostDialog;
    deleteHost* deleteHostDialog;
    AddFlightDialog* addFlightDialog;
};
#endif // MAINWINDOW_H
