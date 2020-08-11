#ifndef FLIGHTSTATUSDIALOG_H
#define FLIGHTSTATUSDIALOG_H

#include <QDialog>
class Flight;

namespace Ui {
class FlightStatusDialog;
}

class FlightStatusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FlightStatusDialog(Flight* flight, QWidget *parent = nullptr);
    ~FlightStatusDialog();

private slots:
    void on_btnAddPilot_clicked();

    void on_btnAddHost_clicked();

    void on_btnAddAirplane_clicked();

    void on_btnAddDCarrier_clicked();

    void on_btnAddACarrier_clicked();

    void on_btnAddTicket_clicked();

    void reset();

    void on_btnEditCheck_clicked();

private:
    Ui::FlightStatusDialog *ui;

    Flight * flight_ptr;
};

#endif // FLIGHTSTATUSDIALOG_H
