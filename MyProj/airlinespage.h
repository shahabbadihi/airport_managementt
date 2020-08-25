#ifndef AIRLINESPAGE_H
#define AIRLINESPAGE_H

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

private:
    Ui::AirlinesPage *ui;
    QString searchcode;
};

#endif // AIRLINESPAGE_H
