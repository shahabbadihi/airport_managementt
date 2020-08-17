#include "mainwindow.h"

#include <QApplication>
#include <QVector>
#include <QFile>
#include <QThread>
#include <QFontDatabase>
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
#include "Carrier.h"
#include "Passenger.h"
#include "ThreadedJob.h"
#include <QDebug>
#include <QDir>


int main(int argc, char *argv[])
{    
    QDir::setCurrent("..");
    //qDebug() << QDir::currentPath();
    //Recorder<Pilot>::print_dataList();
    //
//    qDebug() << "Hello";
//    try{
        Recorder<Flight>::getInstance()->import();
        Recorder<Airline>::getInstance()->import();
        Recorder<Pilot>::getInstance()->import();
        Recorder<Host>::getInstance()->import();
        Recorder<Airplane>::getInstance()->import();
        Recorder<Carrier>::getInstance()->import();
        Recorder<Ticket>::getInstance()->import();
        Recorder<Passenger>::getInstance()->import();
//    } catch (...) {
//        qDebug() << "akbar";
//    }

    //
//    QDate d(2020, 6, 18);
//    QTime t(13, 0);
//    QDate d2(2020, 6, 18);
//    QTime t2(14, 0);
//    QDateTime departure(d, t);
//    QDateTime destination(d2, t2);
//    qint64 seconds = departure.secsTo(destination);
//    double price = (seconds * 5) / 72;
//    qDebug() << QString::number(price);


    qDebug() << "Bye";
    QApplication a(argc, argv);
    qDebug() << "Hi";
    MainWindow w;
    qDebug() << "Fi";

    //QFontDatabase::addApplicationFont(":/fonts/Raleway-Regular.ttf");





    w.setWindowTitle("Main");
    w.show();

//    Recorder<Airline>::getInstance()->import();
//    Recorder<Pilot>::getInstance()->import();
//    Recorder<Host>::getInstance()->import();
//    Recorder<Airplane>::getInstance()->import();
//    Recorder<Carrier>::getInstance()->import();
//    Recorder<Flight>::getInstance()->import();
//    Recorder<Ticket>::getInstance()->import();
//    Recorder<Passenger>::getInstance()->import();

    return a.exec();
}
