#ifndef TICKETPAGE_H
#define TICKETPAGE_H
#include "Ticket.h"
#include <QDialog>
#include <QWidget>
#include <QDataWidgetMapper>
#include "delegate.h"
#include "ticketlistmodel.h"
#include <QSortFilterProxyModel>

namespace Ui {
class TicketPage;
}

class
TicketPage : public QDialog
{
    Q_OBJECT

public:
    explicit TicketPage(Ticket * t,QWidget *parent = nullptr);
    ~TicketPage();
    void update();
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TicketPage *ui;
    Ticket * ticket;

    TicketListModel * model;
    QSortFilterProxyModel * proxy;
};

#endif // TICKETPAGE_H
