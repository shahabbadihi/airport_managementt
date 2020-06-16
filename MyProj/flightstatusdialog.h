#ifndef FLIGHTSTATUSDIALOG_H
#define FLIGHTSTATUSDIALOG_H

#include <QDialog>

namespace Ui {
class FlightStatusDialog;
}

class FlightStatusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FlightStatusDialog(QWidget *parent = nullptr);
    ~FlightStatusDialog();

private:
    Ui::FlightStatusDialog *ui;
};

#endif // FLIGHTSTATUSDIALOG_H
