#include "ThreadedJob.h"
#include "Recorder.h"
#include "Flight.h"
#include "Passenger.h"
#include "flighttablemodel.h"
#include "PilotItemModel.h"


ThreadedJob::ThreadedJob(QObject *parent) : QObject(parent)
{

}

//void ThreadedJob::slt_update_flight_status()
//{
//    foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
//    {
//        f->setState();
//    }
//}

void ThreadedJob::slt_update()
{
    //if (counter % 2 == 0)
    //{
    foreach (Flight* f, Recorder<Flight>::getInstance()->get_dataList())
    {
        f->setState();
    }
    //}
//    if (counter % 2 == 1)
//    {
//        Recorder<Airline>::getInstance()->updateFileAll();
//        Recorder<Airplane>::getInstance()->updateFileAll();
//        Recorder<Host>::getInstance()->updateFileAll();
//        Recorder<Pilot>::getInstance()->updateFileAll();
//        Recorder<Flight>::getInstance()->updateFileAll();
//        Recorder<Passenger>::getInstance()->updateFileAll();
//        Recorder<Ticket>::getInstance()->updateFileAll();
//        Recorder<Carrier>::getInstance()->updateFileAll();
//    }

//    counter++;
}

void ThreadedJob::slt_update_flight_table()
{
    FlightTableModel::getInstance()->timerHit();
}

//void ThreadedJob::slt_update_pilot_model()
//{
//    PilotItemModel::getInstance()->timerHit();
//}


void ThreadedJob::slt_start_update()
{
//    this->counter = 0;

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

//void ThreadedJob::slt_start_update_pilot_model()
//{
//    this->tm_update_pilot_model = new QTimer(this);
//    this->tm_update_pilot_model->setInterval(1000);

//    connect(this->tm_update_pilot_model, SIGNAL(timeout()), this, SLOT(slt_update_pilot_model()));
//    this->tm_update_pilot_model->start();
//}
