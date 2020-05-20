#ifndef RECORDER_H
#define RECORDER_H

#include "TList.h"
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
template <class T>
class Recorder
{
public:
    static void record(T* a)
    {
        Recorder<T>::dataList.push_back(a);
        //Recorder<T>::print_dataList();
    }

    static void addToFile(T* a)
    {
        QDir d(QDir::currentPath() + "/data");
        if (!d.exists())
            d.mkpath(QDir::currentPath() + "/data");
        std::string f = "data/" + std::string(typeid(T).name()).substr(1) + ".txt";
        int len = f.length();
        char* s = new char[len];
        strcpy(s, f.c_str());
        QString filename = QString(s);


        QFile file(filename);
        if (!file.open(QIODevice::Append | QIODevice::Text))
            throw QException();

        //file.open(QFile::Append);

        QTextStream out(&file);
        out << a->get_data();
        //out << "askcn";

        file.flush();
        file.close();

        delete[] s;
    }
    static void removeFromFile(T* a)
    {
        QDir d(QDir::currentPath() + "/data");
        try {
            std::string f = "data/" + std::string(typeid(T).name()).substr(1) + ".txt";
            int len = f.length();
            char* s = new char[len];
            strcpy(s, f.c_str());
            QString filename = QString(s);

            QFile file(filename);
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
                    out << Recorder<T>::get_dataList().at(i)->get_data();
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

    static QVector<T*> get_dataList()
    {
        return Recorder<T>::dataList;
    }

    static void print_dataList()
    {
        for (int i = 0; i < Recorder<T>::dataList.size(); i++)
        {
            qDebug() << Recorder<T>::dataList.at(i)->get_data();
        }
    }

    static void import()
    {
        QDir dataDir(QDir::currentPath() + "/data");
        if (!dataDir.exists())
            dataDir.mkpath(QDir::currentPath() + "/data");
        std::string f = std::string(typeid(T).name()).substr(1);
        int len = f.length();
        char* s = new char[len];
        strcpy(s, f.c_str());
        QString classname = QString(s);


        QString filename = "";
        foreach (QFileInfo finfo, dataDir.entryInfoList())
        {
            //qDebug() << finfo.fileName();
            if (finfo.fileName().startsWith(classname))
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
            Recorder<T>::record(newObj);
        }

        file.close();
        delete[] s;

        Recorder<T>::print_dataList();
    }
    static T * searchPersonnelCode(long p){
        for (int i = 0; i < Recorder<T>::dataList.size(); i++)
        {
            if(Recorder<T>::dataList.at(i)->get_personnelCode()==p){
                return Recorder<T>::dataList.at(i);
            }
        }
        return nullptr;
    }
    static void remove(T * a){
        Recorder<T>::dataList.removeOne(a);
    }
private:
    static QVector<T*> dataList;
};
#endif // RECORDER_H
