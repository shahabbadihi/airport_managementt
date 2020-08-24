#ifndef RECORDER_H
#define RECORDER_H

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
#include <QObject>

class Flight;
class Carrier;

#include "flighttablemodel.h"
#include "SignalSlotRecorder.h"

template <class T>
class Recorder : public SignalSlotRecorder
{
    //Q_OBJECT
public:
//    void addToFile(T* a);
//    void removeFromFile(T* a);

    friend class Ticket;

    QVector<T*> get_dataList();
    bool isInList(T * a);

    void print_dataList();
    void add(T* a);
    void import();

    T * searchByCode(const QString& p);
    bool isSearchCodeExist(const QString& str);

    void remove(T * a);

//    void updateFile(T * ptr);
    void updateFileAll();

    QString getClassName();

    static Recorder<T>* getInstance();

    Recorder<T>()
    {
        setModelPtr();
        if (this->model_ptr)
        {
            connect(this, SIGNAL(recordAdded()), this->model_ptr, SLOT(recordInserted()));
            connect(this, SIGNAL(recordRemovedSignal(int)), this->model_ptr, SLOT(recordRemovedSlot(int)));
        }
    }

    void setModelPtr() {this->model_ptr = nullptr;}

    Carrier* getFirstFree(const QDateTime&, const QString&);
private:
    QVector<T*> dataList;
    static Recorder<T>* instance;
    QAbstractItemModel * model_ptr;

    void record(T* a);
    QString getFileName();

//signals:
//    void recordAdded();

public slots:
    virtual void recordRemovedSlot(int);
};

template <class T>
Recorder<T>* Recorder<T>::instance;

#endif // RECORDER_H
