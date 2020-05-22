#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "addhost.h"
#include <QString>
#include <QDesktopWidget>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pTableWidget = new QTableWidget(this);
     m_pTableWidget->setRowCount(10);
     m_pTableWidget->setColumnCount(3);
     m_TableHeader<<"#"<<"Name"<<"Text";
     m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
     m_pTableWidget->verticalHeader()->setVisible(false);
     m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
     m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
     m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
     m_pTableWidget->setShowGrid(false);
     m_pTableWidget->setStyleSheet("QTableView {selection-background-color: red;}");
     m_pTableWidget->setGeometry(QApplication::desktop()->screenGeometry());

     //insert data
     m_pTableWidget->setItem(0, 1, new QTableWidgetItem("Hello"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAddPilot_triggered()
{
    this->addPilotDialog = new Dialog();
    addPilotDialog->setModal(true);
    addPilotDialog->exec();
    delete addPilotDialog;
}

void MainWindow::on_actionAdd_Host_triggered()
{
    this->addHostDialog = new AddHost();
    addHostDialog->setModal(true);
    addHostDialog->exec();
    delete addHostDialog;
}

void MainWindow::on_btnBuyTicket_clicked()
{

}
