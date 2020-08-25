#include "mainwindow.h"

#include <QApplication>
#include <QVector>
#include <QFile>
#include <QThread>
#include <QFontDatabase>
#include "stdio.h"
#include "Recorder.h"
#include "Host.h"
#include "Pilot.h"
#include "Flight.h"
#include "Carrier.h"
#include "Passenger.h"
#include "ThreadedJob.h"
#include <QDebug>
#include <QDir>

bool ISDATACHANGED = false;

int main(int argc, char *argv[])
{    
    QDir::setCurrent("..");

    Recorder<Carrier>::getInstance()->import();
    Recorder<Flight>::getInstance()->import();
    Recorder<Airline>::getInstance()->import();
    Recorder<Pilot>::getInstance()->import();
    Recorder<Host>::getInstance()->import();
    Recorder<Airplane>::getInstance()->import();
    Recorder<Ticket>::getInstance()->import();
    Recorder<Passenger>::getInstance()->import();

    ISDATACHANGED = false;

    qDebug() << "Bye";
    QApplication a(argc, argv);
    qDebug() << "Hi";
    MainWindow w;
    qDebug() << "Fi";


    w.setWindowTitle("Main");
    w.show();

    return a.exec();
}
