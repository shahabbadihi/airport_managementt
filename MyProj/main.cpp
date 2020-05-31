#include "mainwindow.h"

#include <QApplication>
#include <QVector>
#include <QFile>
#include "stdio.h"
//#include "TList.h"
#include "Recorder.h"
//#include "Airplane.h"
#include "Host.h"
//#include "Passenger.h"
#include "Pilot.h"
//#include "Deliverier.h"
//#include "Ticket.h"
#include "Flight.h"
#include <QDebug>
#include <QDir>


int main(int argc, char *argv[])
{    
    QDir::setCurrent("..");
    //qDebug() << QDir::currentPath();
    Recorder<Pilot>::getInstance()->import();
    Recorder<Host>::getInstance()->import();
    Recorder<Flight>::getInstance()->import();
    //Recorder<Pilot>::print_dataList();
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Main");
    w.show();

    return a.exec();
}
