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
};

#endif // SIGNALSLOTRECORDER_H
