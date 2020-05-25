#ifndef ADDAIRLINEDIALOG_H
#define ADDAIRLINEDIALOG_H

#include <QDialog>

namespace Ui {
class AddAirlineDialog;
}

class AddAirlineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAirlineDialog(QWidget *parent = nullptr);
    ~AddAirlineDialog();

private slots:
    void on_btnSubmit_clicked();

    void on_btnCancel_clicked();

private:
    Ui::AddAirlineDialog *ui;
};

#endif // ADDAIRLINEDIALOG_H
