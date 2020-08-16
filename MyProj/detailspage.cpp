#include "detailspage.h"
#include "ui_detailspage.h"
#include "Flight.h"
#include "ticketpage.h"
DetailsPage::DetailsPage(Flight *f,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailsPage)
{
    flight =f;
    ui->setupUi(this);
    this->model = TicketListModel::getInstance();
    this->proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    proxy->setDynamicSortFilter(true);
    ui->listView->setModel(proxy);
    proxy->setFilterFixedString(flight->getSerial());
}

DetailsPage::~DetailsPage()
{
    delete ui;
}

void DetailsPage::on_listView_clicked(const QModelIndex &index)
{
     QStringList str = index.data().toString().split(" | ");
     TicketPage *t=new TicketPage(Recorder<Ticket>::getInstance()->searchByCode(str[1]));
     t->exec();
}
