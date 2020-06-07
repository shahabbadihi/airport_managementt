#ifndef SIGNALSLOTRECORDER_H
#define SIGNALSLOTRECORDER_H

#include <QObject>

class SignalSlotRecorder : public QObject
{
    Q_OBJECT
protected:
    SignalSlotRecorder(){}
signals:
    void recordAdded();

public slots:
    virtual void recordRemoved(int) = 0;

};

#endif // SIGNALSLOTRECORDER_H
