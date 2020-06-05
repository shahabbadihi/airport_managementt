#ifndef SIGNALSLOT_H
#define SIGNALSLOT_H

#include <QAbstractItemModel>

class SignalSlot : public QAbstractItemModel
{
    Q_OBJECT
protected:
    SignalSlot(QObject *parent = nullptr) : QAbstractItemModel(parent) {}
private slots:
    virtual void timerHit() = 0;
    virtual void recordInserted() = 0;
};

#endif // SIGNALSLOT_H
