#ifndef HOSTSPAGE_H
#define HOSTSPAGE_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "delegate.h"
#include "HostItemModel.h"
#include "Recorder.h"

namespace Ui {
class HostsPage;
}

class HostsPage : public QWidget
{
    Q_OBJECT

public:
    explicit HostsPage(QWidget *parent = nullptr);
    ~HostsPage();
private slots:
    void on_btnSubmit_clicked();
    void updateButtons(int row);
    void setCurrentIndex(int row);
    void updateButtonsWhenRecordAdded();
private:
    Ui::HostsPage *ui;

    HostItemModel * host_item_model;
    Delegate * delegate;
    QDataWidgetMapper * mapper;
};

#endif // HOSTSPAGE_H
