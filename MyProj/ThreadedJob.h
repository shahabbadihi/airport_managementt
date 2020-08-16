#ifndef THREADEDJOB_H
#define THREADEDJOB_H

#include <QObject>
#include <QTimer>

class ThreadedJob : public QObject
{
    Q_OBJECT

private:
    QTimer * tm_update_flight_table;
    QTimer * tm_update;
//    QTimer * tm_update_pilot_model;
    long long counter;
public:
    explicit ThreadedJob(QObject *parent = nullptr);

signals:

private slots:
    void slt_update();
    void slt_update_flight_table();
//    void slt_update_pilot_model();
public slots:
    void slt_start_update();
    void slt_start_update_flight_table();
//    void slt_start_update_pilot_model();
};

#endif // THREADEDJOB_H
