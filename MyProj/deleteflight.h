#ifndef DELETEFLIGHT_H
#define DELETEFLIGHT_H

#include <QDialog>

namespace Ui {
class deleteFlight;
}

class deleteFlight : public QDialog
{
    Q_OBJECT

public:
    explicit deleteFlight(QWidget *parent = nullptr);
    ~deleteFlight();

private:
    Ui::deleteFlight *ui;
};

#endif // DELETEFLIGHT_H
