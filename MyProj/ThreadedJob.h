#ifndef THREADEDJOB_H
#define THREADEDJOB_H

#include <QObject>
#include <QTimer>

class ThreadedJob : public QObject
{
    Q_OBJECT

private:
    QTimer * tm_update_flight_status;
    QTimer * tm_update_files;
    QTimer * tm_update_flight_table;
public:
    explicit ThreadedJob(QObject *parent = nullptr);

signals:

private slots:
    void slt_update_flight_status();
    void slt_update_files();
    void slt_update_flight_table();
public slots:
    void slt_start_update_flight_status();
    void slt_start_update_files();
    void slt_start_update_flight_table();
};

#endif // THREADEDJOB_H
