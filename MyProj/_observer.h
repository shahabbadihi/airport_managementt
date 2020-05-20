#ifndef _OBSERVER_H
#define _OBSERVER_H
class _Subject;

class _Observer
{
public:
    _Observer() : subj_ptr(nullptr) {}

    void update();

    _Subject *getSubjPtr();
    void setSubjPtr(_Subject *);

private:
    _Subject* subj_ptr;
};

#endif // _OBSERVER_H
