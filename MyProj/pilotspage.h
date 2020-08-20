#ifndef PILOTSPAGE_H
#define PILOTSPAGE_H

//#include <QWidget>
//#include <QDataWidgetMapper>
//#include "delegate.h"
//#include "pilotitemmodel.h"
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
//    void viewWage();
private slots:
    void on_btnSubmit_clicked();

    virtual void updateButtons(int row);
private:
    Ui::PilotsPage *ui;

//    PilotItemModel * pilot_item_model;
//    Delegate * delegate;
//    QDataWidgetMapper * mapper;
};

#endif // PILOTSPAGE_H
