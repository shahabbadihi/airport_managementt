#ifndef EDITSEAS_H
#define EDITSEAS_H

#include <QDialog>
#include "Flight.h"
namespace Ui {
class editSeas;
}

class editSeas : public QDialog
{
    Q_OBJECT

public:
    explicit editSeas(Flight * flight,QWidget *parent = nullptr);
    ~editSeas();

private slots:
    void on_pushButton_clicked();

    void on_seatChart_cellActivated(int row, int column);

    void on_seatChart_cellClicked(int row, int column);

private:
    Ui::editSeas *ui;
    Flight * flight;
};

#endif // EDITSEAS_H
