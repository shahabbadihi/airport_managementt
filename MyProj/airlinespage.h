#ifndef AIRLINESPAGE_H
#define AIRLINESPAGE_H

//#include <QWidget>
//#include <QDataWidgetMapper>
//#include "delegate.h"
#include "airlineitemmodel.h"
#include "DataMapperPage.h"
namespace Ui {
class AirlinesPage;
}

class AirlinesPage : public DataMapperPage
{
    Q_OBJECT

public:
    explicit AirlinesPage(QWidget *parent = nullptr);
    ~AirlinesPage();

private slots:
    void on_subBtn_clicked();
    virtual void updateButtons(int);

//    void setCurrentIndex(int row);
//    void updateButtonsWhenRecordAdded();
private:
    Ui::AirlinesPage *ui;
    QString searchcode;
//    AirlineItemModel * airline_item_model;
//    Delegate * delegate;
//    QDataWidgetMapper * mapper;
};

#endif // AIRLINESPAGE_H
