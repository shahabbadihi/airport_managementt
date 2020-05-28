#ifndef ADDCARRIERDIALOG_H
#define ADDCARRIERDIALOG_H

#include <QDialog>

namespace Ui {
class AddCarrierDialog;
}

class AddCarrierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCarrierDialog(QWidget *parent = nullptr);
    ~AddCarrierDialog();

private slots:
    void on_btnSubmit_clicked();

    void on_btnCancel_clicked();

private:
    Ui::AddCarrierDialog *ui;
};

#endif // ADDCARRIERDIALOG_H
