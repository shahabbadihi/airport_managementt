#include "GetPassengerFactory.h"
#include "Recorder.h"
#include "Ticket.h"
#include "Flight.h"
#include "PU2.h"
#include "P2_12.h"
#include "PO12.h"

GetPassengerFactory* GetPassengerFactory::instance;

GetPassengerFactory::GetPassengerFactory()
{

}

GetPassengerFactory *GetPassengerFactory::getInstance()
{
    if (instance == nullptr)
        instance = new GetPassengerFactory;
    return instance;
}

Passenger *GetPassengerFactory::getPassenger(const QDate &birth, const QDate &dep_date,
                                             qlonglong national_code,
                                             const QString &fname,
                                             const QString &lname,
                                             const QString &father_name)
{
    int age = dep_date.year() - birth.year();
    if (birth > dep_date.addYears(-age))
        age--;
    if (age < 2)
    {
        QString search_code = QString::number(national_code) + "A";
        if (!Recorder<Passenger>::getInstance()->searchByCode(search_code))
        {
            return new PU2(national_code, fname, lname, birth, father_name);
        }
        else
            return Recorder<Passenger>::getInstance()->searchByCode(search_code);
    }
    else if (age >= 2 && age <= 12)
    {
        QString search_code = QString::number(national_code) + "B";
        if (!Recorder<Passenger>::getInstance()->searchByCode(search_code))
        {
            return new P2_12(national_code, fname, lname, birth, father_name);
        }
        else
            return Recorder<Passenger>::getInstance()->searchByCode(search_code);
    }
    else if (age > 12)
    {
        QString search_code = QString::number(national_code) + "C";
        if (!Recorder<Passenger>::getInstance()->searchByCode(search_code))
        {
            return new PO12(national_code, fname, lname, birth, father_name);
        }
        else
            return Recorder<Passenger>::getInstance()->searchByCode(search_code);
    }
}


Passenger *GetPassengerFactory::getPassenger(QString &str_data)
{
    QStringList str_list = str_data.split('|');
    QStringList birth_date = str_list.at(4).split('/', Qt::SkipEmptyParts);
    QStringList tickets = str_list[5].split('/', Qt::SkipEmptyParts);
    if (tickets.size() == 0)
    {
        return nullptr;
    }

    QDate dt1(birth_date[2].toInt(), birth_date[0].toInt(), birth_date[1].toInt());
    QDate dt2(Recorder<Ticket>::getInstance()->searchByCode(tickets[0])->getFlight()->getDateTimeDeparture().date());
    int age = dt2.year() - dt1.year();
    if (dt1 > dt2.addYears(-age))
        age--;

    if (!Recorder<Passenger>::getInstance()->searchByCode(str_list[0]))
    {
        if (age < 2)
        {
            return new Passenger(str_data);
        }
        if (age >= 2 && age <= 12)
        {
            return new Passenger(str_data);
        }
        if (age > 12)
        {
            return new Passenger(str_data);
        }
    }
    return Recorder<Passenger>::getInstance()->searchByCode(str_list[0]);
}
