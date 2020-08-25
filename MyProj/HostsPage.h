#ifndef HOSTSPAGE_H
#define HOSTSPAGE_H

#include "DataMapperPage.h"
#include "Recorder.h"

namespace Ui {
class HostsPage;
}

class HostsPage : public DataMapperPage
{
    Q_OBJECT

public:
    explicit HostsPage(QWidget *parent = nullptr);
    ~HostsPage();
private slots:
    void on_btnSubmit_clicked();
    void updateButtons(int row);
private:
    Ui::HostsPage *ui;

};

#endif // HOSTSPAGE_H
