#ifndef ATTACHTICKET_H
#define ATTACHTICKET_H

#include <QDialog>
#include "Flight.h"
namespace Ui {
class attachTicket;
}

class attachTicket : public QDialog
{
    Q_OBJECT

public:
    explicit attachTicket(Flight *flight ,int row ,int col,QWidget *parent = nullptr);
    ~attachTicket();

private slots:
    void on_okButton_clicked();

    void on_editButton_clicked();

private:
    Ui::attachTicket *ui;
    Flight *flight;
    int Row;
    int Column;
};

#endif // ATTACHTICKET_H
