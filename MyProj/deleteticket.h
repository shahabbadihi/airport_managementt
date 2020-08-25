#ifndef DELETETICKET_H
#define DELETETICKET_H

#include <QDialog>
#include <QSortFilterProxyModel>
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

    void on_deleteButton_clicked();


    void on_cancelButton_clicked();


private:
    Ui::deleteTicket *ui;

    TicketListModel * model;
    QSortFilterProxyModel * proxy;
};

#endif // DELETETICKET_H
