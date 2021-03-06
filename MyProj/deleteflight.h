#ifndef DELETEFLIGHT_H
#define DELETEFLIGHT_H

#include <QDialog>
#include "flightlistmodel.h"

namespace Ui {
class deleteFlight;
}

class deleteFlight : public QDialog
{
    Q_OBJECT

public:
    explicit deleteFlight(QWidget *parent = nullptr);
    ~deleteFlight();

private slots:
    void on_pushButton_clicked();

private slots:
    void on_pushButton_2_clicked();
    
private:
    Ui::deleteFlight *ui;

    FlightListModel * model;
};

#endif // DELETEFLIGHT_H
