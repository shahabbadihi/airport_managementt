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
class Flight;
template <class T>
class Recorder
{
public:
    void record(T* a)
    {
        this->dataList.push_back(a);
        //Recorder<T>::print_dataList();
    }

    void addToFile(T* a)
    {
        QDir d(QDir::currentPath() + "/data");
        if (!d.exists())
            d.mkpath(QDir::currentPath() + "/data");
//        std::string f = "data/" + std::string(typeid(T).name()).substr(1) + ".txt";
//        int len = f.length();
//        char* s = new char[len];
//        strcpy(s, f.c_str());
//        QString filename = QString(s);


        QFile file("data/" + this->getClassName() + ".txt");
        if (!file.open(QIODevice::Append | QIODevice::Text))
            throw QException();

        //file.open(QFile::Append);

        QTextStream out(&file);
        out << a->get_data();
        //out << "askcn";

        file.flush();
        file.close();
    }
    void removeFromFile(T* a)
    {
        QDir d(QDir::currentPath() + "/data");
        try {
//            std::string f = "data/" + std::string(typeid(T).name()).substr(1) + ".txt";
//            int len = f.length();
//            char* s = new char[len];
//            strcpy(s, f.c_str());
//            QString filename = QString(s);

            QFile file("data/" + this->getClassName() + ".txt");
            if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
                throw QException();

            QTextStream txt(&file);
            int flag = 0, num_of_line = 0, lines_count = 0;

            while (!txt.atEnd())
            {
                txt.readLine();
                lines_count++;
            }

            txt.seek(0);

            while (!txt.atEnd())
            {
                QString data_str = txt.readLine();
                if (data_str + "\n" == a->get_data())
                {
                    flag = 1;
                    break;
                }
                num_of_line++;
            }
            if (flag == 1)
            {
                file.resize(0);
                QTextStream out(&file);
                for (int i = 0; i < lines_count; i++)
                {
                    if (i == num_of_line)
                        continue;
                    out << this->get_dataList().at(i)->get_data();
                }
            }
            file.flush();
            file.close();


        } catch (QException) {
            QMessageBox msg;
            msg.setText("File Not Found!");
            msg.exec();
        }

    }

    QVector<T*> get_dataList()
    {
        return this->dataList;
    }

    void print_dataList()
    {
        for (int i = 0; i < this->dataList.size(); i++)
        {
            qDebug() << this->dataList.at(i)->get_data();
        }
    }
    void add(T* a)
    {
        this->record(a);
        this->addToFile(a);
    }
    void import()
    {
        QDir dataDir(QDir::currentPath() + "/data");
        if (!dataDir.exists())
            dataDir.mkpath(QDir::currentPath() + "/data");
//        std::string f = std::string(typeid(T).name()).substr(1);
//        int len = f.length();
//        char* s = new char[len];
//        strcpy(s, f.c_str());
//        QString classname = QString(s);


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
            //throw QException();
        }
        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString dataString = in.readLine();
            T* newObj = new T(dataString);
            this->record(newObj);
        }

        file.close();

        this->print_dataList();
    }

    T * searchByCode(const QString& p){
        for (int i = 0; i < this->dataList.size(); i++)
        {
            if(this->dataList.at(i)->getSearchCode()==p){
                return this->dataList.at(i);
            }
        }
        return nullptr;
    }
    void remove(T * a)
    {
        this->removeFromFile(a);
        this->dataList.removeOne(a);
        delete a;
    }

//    static T* getFirstFree(Flight* f)
//    {
//        for (int i = 0; i < Recorder<T>::dataList.size(); i++)
//        {
//            T* a = Recorder<T>::dataList.at(i);
//            if (a->isFree(f))
//                return a;
//        }
//        return nullptr;
//    }

    void updateFile(T * ptr)
    {
        QDir d(QDir::currentPath() + "/data");
//        std::string f = "data/" + std::string(typeid(T).name()).substr(1) + ".txt";
//        int len = f.length();
//        char* s = new char[len];
//        strcpy(s, f.c_str());
//        QString filename = QString(s);

        QFile file("data/" + this->getClassName() + ".txt");
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            throw QException();

        QString str = file.readAll();
        QStringList str_list = str.split('\n');

        for (int i = 0; i < str_list.size(); i++)
        {
            if (str_list[i].indexOf(ptr->getSearchCode()) != -1)
            {
                str_list[i] = ptr->get_data();
                break;
            }
        }

        str_list.replaceInStrings("\n", "");
        QString str2 = str_list.join('\n');
        file.resize(0);


        QTextStream out(&file);
        out << str2;

        file.flush();
        file.close();
    }

    QString getClassName()
    {
        std::string f = std::string(typeid(T).name()).substr(1);
        int len = f.length();
        char* s = new char[len];
        strcpy(s, f.c_str());
        QString filename = QString(s);
        delete[] s;
        return filename;
    }
    static Recorder<T>* getInstance()
    {
        if (instance == nullptr)
            instance = new Recorder<T>;
        return instance;
    }

    Recorder<T>() {}
private:
    QVector<T*> dataList;
    static Recorder<T>* instance;
};

#endif // RECORDER_H
