#ifndef _SUBJECT_H
#define _SUBJECT_H
#include <QVector>
class _Observer;

class _Subject
{
public:
    _Subject();

    void attach(_Observer*);
    void dettach(_Observer*);
    void notify();
private:
    QVector<_Observer*> obs_list;
};

#endif // _SUBJECT_H
