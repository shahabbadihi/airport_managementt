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
    void recordRemovedSignal(int);

public slots:
    virtual void recordRemovedSlot(int) = 0;

};

#endif // SIGNALSLOTRECORDER_H
