#ifndef DETAILSPAGE_H
#define DETAILSPAGE_H
#include "Flight.h"
#include <QDialog>
#include "ticketlistmodel.h"
#include <QSortFilterProxyModel>

namespace Ui {
class DetailsPage;
}

class DetailsPage : public QDialog
{
    Q_OBJECT

public:
    explicit DetailsPage(Flight *f,QWidget *parent = nullptr);
    ~DetailsPage();

private slots:
    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::DetailsPage *ui;
    Flight *flight;

    TicketListModel * model;
    QSortFilterProxyModel * proxy;
};

#endif // DETAILSPAGE_H
