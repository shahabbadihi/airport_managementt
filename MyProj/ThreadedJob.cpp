#include "ThreadedJob.h"
#include "Recorder.h"
#include "Flight.h"
#include "Passenger.h"
#include "flighttablemodel.h"

ThreadedJob::ThreadedJob(QObject *parent) : QObject(parent)
{

}

void ThreadedJob::slt_update_flight_status()
{
    foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
    {
        f->setState();
    }
}

void ThreadedJob::slt_update_files()
{
    Recorder<Airline>::getInstance()->updateFileAll();
    Recorder<Airplane>::getInstance()->updateFileAll();
    Recorder<Host>::getInstance()->updateFileAll();
    Recorder<Pilot>::getInstance()->updateFileAll();
    Recorder<Flight>::getInstance()->updateFileAll();
    Recorder<Passenger>::getInstance()->updateFileAll();
    Recorder<Ticket>::getInstance()->updateFileAll();
    Recorder<Carrier>::getInstance()->updateFileAll();
}

void ThreadedJob::slt_update_flight_table()
{
    FlightTableModel::getInstance()->timerHit();
}

void ThreadedJob::slt_start_update_flight_status()
{
    this->tm_update_flight_status = new QTimer(this);
    this->tm_update_flight_status->setInterval(1000);

    connect(this->tm_update_flight_status, SIGNAL(timeout()), this, SLOT(slt_update_flight_status()));
    this->tm_update_flight_status->start();
}

void ThreadedJob::slt_start_update_files()
{
    this->tm_update_files = new QTimer(this);
    this->tm_update_files->setInterval(10000);

    connect(this->tm_update_files, SIGNAL(timeout()), this, SLOT(slt_update_files()));
    this->tm_update_files->start();
}

void ThreadedJob::slt_start_update_flight_table()
{
    this->tm_update_flight_table = new QTimer(this);
    this->tm_update_flight_table->setInterval(1000);

    connect(this->tm_update_flight_table, SIGNAL(timeout()), this, SLOT(slt_update_flight_table()));
    this->tm_update_flight_table->start();
}
