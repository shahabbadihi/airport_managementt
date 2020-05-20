#ifndef ADDHOST_H
#define ADDHOST_H

#include <QDialog>

namespace Ui {
class AddHost;
}

class AddHost : public QDialog
{
    Q_OBJECT

public:
    explicit AddHost(QWidget *parent = nullptr);
    ~AddHost();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddHost *ui;
};

#endif // ADDHOST_H
