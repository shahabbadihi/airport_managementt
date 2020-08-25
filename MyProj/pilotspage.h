#ifndef PILOTSPAGE_H
#define PILOTSPAGE_H

#include "DataMapperPage.h"
#include "Recorder.h"
namespace Ui {
class PilotsPage;
}

class PilotsPage : public DataMapperPage
{
    Q_OBJECT

public:
    explicit PilotsPage(QWidget *parent = nullptr);
    ~PilotsPage();
private slots:
    void on_btnSubmit_clicked();

    virtual void updateButtons(int row);
private:
    Ui::PilotsPage *ui;

};

#endif // PILOTSPAGE_H
