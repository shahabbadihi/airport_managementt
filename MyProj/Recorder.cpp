#include "Recorder.h"
#include "Carrier.h"
#include "Flight.h"
#include "Host.h"
#include "Pilot.h"
#include "pd1.h"
#include "pd2.h"
#include "pd3.h"
#include "Ticket.h"
#include "Passenger.h"
#include "getpassengerfactory.h"
//#include "pu2.h"
//#include "po12.h"
//#include "p2_12.h"
#include "Airline.h"
#include "Airplane.h"
#include <QVector>
#include <stdexcept>
using namespace std;
//#include "mymodel.h"
#include "flighttablemodel.h"

extern bool ISDATACHANGED;

template<class T>
void Recorder<T>::record(T *a)
{
    if (a && !this->isInList(a))
    {
        this->dataList.push_back(a);
        emit recordAdded();
    }
    //Recorder<T>::print_dataList();
}

//template<class T>
//void Recorder<T>::addToFile(T *a)
//{
//    QDir d(QDir::currentPath() + "/data");
//    if (!d.exists())
//        d.mkpath(QDir::currentPath() + "/data");


//    QFile file("data/" + this->getClassName() + ".txt");
//    if (!file.open(QIODevice::Append | QIODevice::Text))
//        throw QException();

//    //file.open(QFile::Append);

//    QTextStream out(&file);
//    out << a->get_data();
//    //out << "askcn";

//    file.flush();
//    file.close();
//}

//template<class T>
//void Recorder<T>::removeFromFile(T *a)
//{
//    QDir d(QDir::currentPath() + "/data");
//    try {

//        QFile file("data/" + this->getClassName() + ".txt");
//        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
//            throw QException();

//        QTextStream txt(&file);
//        int flag = 0, num_of_line = 0, lines_count = 0;

//        while (!txt.atEnd())
//        {
//            txt.readLine();
//            lines_count++;
//        }

//        txt.seek(0);

//        while (!txt.atEnd())
//        {
//            QString data_str = txt.readLine();
//            if (data_str + "\n" == a->get_data())
//            {
//                flag = 1;
//                break;
//            }
//            num_of_line++;
//        }
//        if (flag == 1)
//        {
//            file.resize(0);
//            QTextStream out(&file);
//            for (int i = 0; i < lines_count; i++)
//            {
//                if (i == num_of_line)
//                    continue;
//                out << this->get_dataList().at(i)->get_data();
//            }
//        }
//        file.flush();
//        file.close();


//    } catch (QException) {
//        QMessageBox msg;
//        msg.setText("File Not Found!");
//        msg.exec();
//    }

//}

template<class T>
QVector<T *> Recorder<T>::get_dataList()
{
    return this->dataList;
}

template<class T>
bool Recorder<T>::isInList(T *a)
{
    foreach (T* t, this->dataList)
    {
        if (a == t)
            return true;
    }
    return false;
}

template<class T>
void Recorder<T>::print_dataList()
{
    for (int i = 0; i < this->dataList.size(); i++)
    {
        qDebug() << this->dataList.at(i)->get_data();
    }
}

template<class T>
void Recorder<T>::add(T *a)
{
    QString str = a->getSearchCode();

    if (this->isSearchCodeExist(str))
    {
        QString str2 = this->getClassName() + " With Code " + str + " Already Exist!";
        throw invalid_argument(str2.toStdString());
    }

    if (a && !this->isInList(a))
    {
        this->record(a);
//        Recorder<T>::getInstance()->updateFileAll();
        ISDATACHANGED = true;
    }
    //this->addToFile(a);
}

template<class T>
void Recorder<T>::import()
{
    QDir dataDir(QDir::currentPath() + "/data");
    if (!dataDir.exists())
        dataDir.mkpath(QDir::currentPath() + "/data");


    QString filename = "";
    foreach (QFileInfo finfo, dataDir.entryInfoList())
    {
        //qDebug() << finfo.fileName();
        if (finfo.fileName().startsWith(this->getClassName()))
        {
            filename = finfo.fileName();
            break;
        }
    }

    QFile file("data/" + filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        file.open(QIODevice::WriteOnly);
    }
    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString dataString = in.readLine();
        T* newObj = new T(dataString);
        this->add(newObj);
    }

    file.close();

    //this->print_dataList();
}

template<class T>
T *Recorder<T>::searchByCode(const QString &p){
    for (int i = 0; i < this->dataList.size(); i++)
    {
        if(this->dataList.at(i)->getSearchCode()==p){
            return this->dataList.at(i);
        }
    }
    return nullptr;
}

template<class T>
bool Recorder<T>::isSearchCodeExist(const QString & search_code)
{
    foreach (T* t, this->dataList)
    {
        if (t->getSearchCode() == search_code)
        {
            return true;
        }
    }
    return false;
}

template<>
bool Recorder<Pilot>::isSearchCodeExist(const QString & search_code)
{
    foreach (Employee* e, Recorder<Employee>::getInstance()->get_dataList())
    {
        if (e->getSearchCode() == search_code)
        {
            return true;
        }
    }
    return false;
}

template<>
bool Recorder<Host>::isSearchCodeExist(const QString & search_code)
{
    foreach (Employee* e, Recorder<Employee>::getInstance()->get_dataList())
    {
        if (e->getSearchCode() == search_code)
        {
            return true;
        }
    }
    return false;
}


template<class T>
void Recorder<T>::remove(T *a)
{
    int index = this->dataList.indexOf(a);
    //this->removeFromFile(a);
    this->dataList.removeOne(a);
    delete a;
    emit recordRemovedSignal(index);

//    Recorder<T>::getInstance()->updateFileAll();
    ISDATACHANGED = true;
}

//template<class T>
//void Recorder<T>::updateFile(T *ptr)
//{
//    QFile file("data/" + this->getClassName() + ".txt");
//    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
//        throw QException();

//    QString str = file.readAll();
//    QStringList str_list = str.split('\n');

//    for (int i = 0; i < str_list.size(); i++)
//    {
//        if (str_list[i].indexOf(ptr->getSearchCode()) != -1)
//        {
//            str_list[i] = ptr->get_data();
//            break;
//        }
//    }

//    str_list.replaceInStrings("\n", "");
//    QString str2 = str_list.join('\n');
//    file.resize(0);


//    QTextStream out(&file);
//    out << str2;

//    file.flush();
//    file.close();
//}

template<class T>
void Recorder<T>::updateFileAll()
{
    QFile file("data/" + this->getClassName() + ".txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        throw QException();

    //QString str = file.readAll();
    //QStringList str_list = str.split('\n', Qt::SkipEmptyParts);
    QString str = "";
    for (int i = 0; i < this->dataList.size(); i++)
    {
        //str_list[i] = this->dataList[i]->get_data();
        str += this->dataList[i]->get_data();
    }

    //str_list.replaceInStrings("\n", "");
    //QString str2 = str_list.join('\n');
    file.resize(0);


    QTextStream out(&file);
    out << str;

    file.flush();
    file.close();
}

template<class T>
QString Recorder<T>::getClassName()
{
    std::string f = std::string(typeid(T).name()).substr(1);
    int len = f.length();
    char* s = new char[len];
    strcpy(s, f.c_str());
    QString filename = QString(s);
    //delete[] s;
    return filename;
}

template<class T>
Recorder<T> *Recorder<T>::getInstance()
{
    if (instance == nullptr)
        instance = new Recorder<T>;
    return instance;
}

//template<class T>
//Recorder<T>::Recorder()
//{
//    this->model_ptr = MyModel::getInstance();
//    connect(this, SIGNAL(recordAdded()), this->model_ptr, SLOT(recordInserted()));
//}

template<>
Carrier* Recorder<Carrier>::getFirstFree(const QDateTime& t, const QString& s)
{
    foreach (Carrier* c, this->get_dataList())
    {
        if (c->isFree(t, s))
            return c;
    }
    return nullptr;
}


template<>
void Recorder<Host>::add(Host * h)
{
    QString str = h->getSearchCode();

    if (this->isSearchCodeExist(str))
    {
        QString str2 = "Employee With Code " + str + " Already Exist!";
        throw invalid_argument(str2.toStdString());
    }
    if (h && !this->isInList(h))
    {
        this->record(h);
        Recorder<Employee>::getInstance()->add(h);
//        Recorder<Host>::getInstance()->updateFileAll();
        ISDATACHANGED = true;
    }
}

template<>
void Recorder<Pilot>::add(Pilot * p)
{
    QString str = p->getSearchCode();

    if (this->isSearchCodeExist(str))
    {
        QString str2 = "Employee With Code " + str + " Already Exist!";
        throw invalid_argument(str2.toStdString());
    }

    if (p && !this->isInList(p))
    {
        this->record(p);
        Recorder<Employee>::getInstance()->add(p);
//        Recorder<Pilot>::getInstance()->updateFileAll();
        ISDATACHANGED = true;
    }
}


template<class T>
void Recorder<T>::recordRemovedSlot(int index)
{
    this->remove(this->dataList[index]);
}


//template<>
//void Recorder<Flight>::record(Flight *a)
//{
//    this->model_ptr = FlightTableModel::getInstance();
//    connect(this, SIGNAL(recordAdded()), this->model_ptr, SLOT(recordInserted()));
//    this->dataList.push_back(a);
//    emit recordAdded();
//}

template<>
void Recorder<Pilot>::import()
{
    QDir dataDir(QDir::currentPath() + "/data");
    if (!dataDir.exists())
        dataDir.mkpath(QDir::currentPath() + "/data");


    QString filename = "";
    foreach (QFileInfo finfo, dataDir.entryInfoList())
    {
        //qDebug() << finfo.fileName();
        if (finfo.fileName().startsWith(this->getClassName()))
        {
            filename = finfo.fileName();
            break;
        }
    }

    QFile file("data/" + filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        file.open(QIODevice::WriteOnly);
    }
    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString dataString = in.readLine();
        QStringList sl = dataString.split('|');

        Pilot* newObj = nullptr;
        if (sl[4] == "1")
            newObj = new PD1(dataString);
        if (sl[4] == "2")
            newObj = new PD2(dataString);
        if (sl[4] == "3")
            newObj = new PD3(dataString);

        this->add(newObj);
    }

    file.close();

    //this->print_dataList();
}

template<>
void Recorder<Passenger>::import()
{
    QDir dataDir(QDir::currentPath() + "/data");
    if (!dataDir.exists())
        dataDir.mkpath(QDir::currentPath() + "/data");


    QString filename = "";
    foreach (QFileInfo finfo, dataDir.entryInfoList())
    {
        //qDebug() << finfo.fileName();
        if (finfo.fileName().startsWith(this->getClassName()))
        {
            filename = finfo.fileName();
            break;
        }
    }

    QFile file("data/" + filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        file.open(QIODevice::WriteOnly);
    }
    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString dataString = in.readLine();
//        QStringList sl = dataString.split('|');
//        QStringList date = sl[4].split('/');
//        QDate dt(date[2].toInt(), date[0].toInt(), date[1].toInt());

        Passenger* newObj = GetPassengerFactory::getInstance()->getPassenger(dataString);
        this->add(newObj);
    }

    file.close();

    //this->print_dataList();
}


template<>
void Recorder<Flight>::setModelPtr()
{
    this->model_ptr = FlightTableModel::getInstance();
}

template class Recorder<Flight>;
template class Recorder<Host>;
template class Recorder<Pilot>;
template class Recorder<Ticket>;
template class Recorder<Passenger>;
template class Recorder<Airplane>;
template class Recorder<Airline>;
template class Recorder<Carrier>;
