#include "ThreadedJob.h"
#include "Recorder.h"
#include "Flight.h"
#include "Passenger.h"
#include "flighttablemodel.h"
#include "PilotItemModel.h"


ThreadedJob::ThreadedJob(QObject *parent) : QObject(parent)
{

}

void ThreadedJob::slt_update()
{
    foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
    {
        f->setState();
    }
}

void ThreadedJob::slt_update_flight_table()
{
    FlightTableModel::getInstance()->timerHit();
}

void ThreadedJob::slt_start_update()
{
    this->tm_update = new QTimer(this);
    this->tm_update->setInterval(60000);

    connect(this->tm_update, SIGNAL(timeout()), this, SLOT(slt_update()));
    this->tm_update->start();
}

void ThreadedJob::slt_start_update_flight_table()
{
    this->tm_update_flight_table = new QTimer(this);
    this->tm_update_flight_table->setInterval(1000);

    connect(this->tm_update_flight_table, SIGNAL(timeout()), this, SLOT(slt_update_flight_table()));
    this->tm_update_flight_table->start();
}
