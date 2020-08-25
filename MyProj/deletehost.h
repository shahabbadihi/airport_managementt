#ifndef DELETEHOST_H
#define DELETEHOST_H

#include <QDialog>
#include "hostlistmodel.h"
namespace Ui {
class deleteHost;
}

class deleteHost : public QDialog
{
    Q_OBJECT

public:
    explicit deleteHost(QWidget *parent = nullptr);
    ~deleteHost();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::deleteHost *ui;

    HostListModel * model;
};

#endif // DELETEHOST_H
