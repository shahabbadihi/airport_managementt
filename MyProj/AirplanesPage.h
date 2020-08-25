#ifndef AIRPLANESPAGE_H
#define AIRPLANESPAGE_H

#include "AirplaneItemModel.h"
#include "DataMapperPage.h"

namespace Ui {
class AirplanesPage;
}

class AirplanesPage : public DataMapperPage
{
    Q_OBJECT

public:
    explicit AirplanesPage(QWidget *parent = nullptr);
    ~AirplanesPage();

private slots:
    void on_btnSubmit_clicked();
    void updateButtons(int row);
private:
    Ui::AirplanesPage *ui;

};

#endif // AIRPLANESPAGE_H
