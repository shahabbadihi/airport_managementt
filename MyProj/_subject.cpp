#include "_subject.h"
#include "_observer.h"
_Subject::_Subject()
{

}

void _Subject::attach(_Observer* o)
{
    this->obs_list.push_back(o);

}

void _Subject::dettach(_Observer* o)
{
    this->obs_list.remove(this->obs_list.lastIndexOf(o));
}

void _Subject::notify()
{
    for (int i = 0; i < this->obs_list.size(); i++)
    {
        this->obs_list.at(i)->update();
    }
}
