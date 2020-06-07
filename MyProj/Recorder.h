#ifndef RECORDER_H
#define RECORDER_H

//#include "TList.h"
//#include "Employee.h"
//#include "Pilot.h"
//#include "Host.h"
#include <QFile>
#include <QDir>
#include <QString>
#include <QTextStream>
#include <typeinfo>
#include <iostream>
#include <bits/stdc++.h>
#include <QException>
#include <QDebug>
#include <QMessageBox>
//#include "Carrier.h"
//#include <string>
//class Employee;
//class Pilot;
//class Host;
//class Flight;
class Carrier;
template <class T>
class Recorder
{
public:
    void record(T* a);

    void addToFile(T* a);
    void removeFromFile(T* a);

    QVector<T*> get_dataList();

    void print_dataList();
    void add(T* a);
    void import();

    T * searchByCode(const QString& p);

    void remove(T * a);

    void updateFile(T * ptr);
    void updateFileAll();

    QString getClassName();
    static Recorder<T>* getInstance();

    Recorder<T>() {}

    Carrier* getFirstFree(const QDateTime&, const QString&);
private:
    QVector<T*> dataList;
    static Recorder<T>* instance;
};


#endif // RECORDER_H
