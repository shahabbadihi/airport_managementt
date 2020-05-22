#ifndef ADDFLIGHTDIALOG_H
#define ADDFLIGHTDIALOG_H

#include <QDialog>

namespace Ui {
class AddFlightDialog;
}

class AddFlightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFlightDialog(QWidget *parent = nullptr);
    ~AddFlightDialog();

private slots:
    void on_btnSubmit_clicked();

    void on_btnCancel_clicked();

private:
    Ui::AddFlightDialog *ui;
};

#endif // ADDFLIGHTDIALOG_H
