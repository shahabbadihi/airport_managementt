#ifndef OBJECT_H
#define OBJECT_H
#include <QString>
#include "Recorder.h"

class Object
{
public:
    virtual QString get_data() = 0;
    //Object() {}
    //~Object() {}
    /*Recorder<Object>& get_recorder()
    {
        return *recorder;
    }*/
    QString getSearchCode() const
    {
        return this->search_code;
    };

protected:
    //Recorder<Object>* recorder;
    QString search_code;
};

#endif // OBJECT_H
