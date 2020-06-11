#ifndef DELETETICKET_H
#define DELETETICKET_H

#include <QDialog>
#include "ticketlistmodel.h"

namespace Ui {
class deleteTicket;
}

class deleteTicket : public QDialog
{
    Q_OBJECT

public:
    explicit deleteTicket(QWidget *parent = nullptr);
    ~deleteTicket();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_deleteButton_clicked();

private:
    Ui::deleteTicket *ui;

    TicketListModel * model;
};

#endif // DELETETICKET_H
