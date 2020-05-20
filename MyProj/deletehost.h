#ifndef DELETEHOST_H
#define DELETEHOST_H

#include <QDialog>

namespace Ui {
class deleteHost;
}

class deleteHost : public QDialog
{
    Q_OBJECT

public:
    explicit deleteHost(QWidget *parent = nullptr);
    ~deleteHost();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    //void on_txtPersonnelCode_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::deleteHost *ui;
};

#endif // DELETEHOST_H
