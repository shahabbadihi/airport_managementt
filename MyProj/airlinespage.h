#ifndef AIRLINESPAGE_H
#define AIRLINESPAGE_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "delegate.h"
#include "airlineitemmodel.h"
namespace Ui {
class AirlinesPage;
}

class AirlinesPage : public QWidget
{
    Q_OBJECT

public:
    explicit AirlinesPage(QWidget *parent = nullptr);
    ~AirlinesPage();
    void  updateButton(int);
private slots:
    void on_subBtn_clicked();

private:
    Ui::AirlinesPage *ui;
    QString searchcode;
    AirlineItemModel * airline_item_model;
    Delegate * delegate;
    QDataWidgetMapper * mapper;
};

#endif // AIRLINESPAGE_H
