#ifndef OBJECT_H
#define OBJECT_H
#include <QString>
#include <QObject>
#include "Recorder.h"

class Object : public QObject
{
    Q_OBJECT

public:
    QString getSearchCode() const
    {
        return this->search_code;
    }
protected:
    virtual QString get_data() = 0;
    //Object() {}
    virtual ~Object() {}
    /*Recorder<Object>& get_recorder()
    {
        return *recorder;
    }*/


    void setSearchCode(const QString& s)
    {

        this->search_code = s;
    }

private:
    //Recorder<Object>* recorder;
    QString search_code;
};

#endif // OBJECT_H
