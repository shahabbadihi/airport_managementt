#ifndef AIRPLANESPAGE_H
#define AIRPLANESPAGE_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "delegate.h"
#include "AirplaneItemModel.h"

namespace Ui {
class AirplanesPage;
}

class AirplanesPage : public QWidget
{
    Q_OBJECT

public:
    explicit AirplanesPage(QWidget *parent = nullptr);
    ~AirplanesPage();

private slots:
    void on_btnSubmit_clicked();
    void updateButtons(int row);
    void setCurrentIndex(int row);
    void updateButtonsWhenRecordAdded();
private:
    Ui::AirplanesPage *ui;

    AirplaneItemModel * airplane_item_model;
    Delegate * delegate;
    QDataWidgetMapper * mapper;
};

#endif // AIRPLANESPAGE_H
