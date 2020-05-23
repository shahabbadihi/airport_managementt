#ifndef OBJECT_H
#define OBJECT_H
#include <QString>
#include "Recorder.h"

class Object
{
public:
    virtual QString get_data() = 0;
    Object() {}
    ~Object() {}
    /*Recorder<Object>& get_recorder()
    {
        return *recorder;
    }*/
private:
    //Recorder<Object>* recorder;
};

#endif // OBJECT_H
