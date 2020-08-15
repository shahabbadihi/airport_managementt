#ifndef PILOTSPAGE_H
#define PILOTSPAGE_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "delegate.h"
#include "pilotitemmodel.h"

namespace Ui {
class PilotsPage;
}

class PilotsPage : public QWidget
{
    Q_OBJECT

public:
    explicit PilotsPage(QWidget *parent = nullptr);
    ~PilotsPage();

private slots:
    void on_btnSubmit_clicked();
    void updateButtons(int row);
    void setCurrentIndex(int row);
    void updateButtonsWhenRecordAdded();
private:
    Ui::PilotsPage *ui;

    PilotItemModel * pilot_item_model;
    Delegate * delegate;
    QDataWidgetMapper * mapper;
};

#endif // PILOTSPAGE_H
