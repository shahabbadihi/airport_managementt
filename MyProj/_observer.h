#ifndef _OBSERVER_H
#define _OBSERVER_H
class _Subject;
#include <QVector>
class _Observer
{
public:
    _Observer() {}

    void update();

    _Subject *getSubjPtr();
    void setSubjPtr(_Subject *);

private:
    QVector<_Subject*> subj_ptr;
};

#endif // _OBSERVER_H
