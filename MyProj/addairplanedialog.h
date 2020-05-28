#ifndef ADDAIRPLANEDIALOG_H
#define ADDAIRPLANEDIALOG_H

#include <QDialog>

namespace Ui {
class AddAirplaneDialog;
}

class AddAirplaneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAirplaneDialog(QWidget *parent = nullptr);
    ~AddAirplaneDialog();

private slots:
    void on_btnSubmit_clicked();

    void on_btnCancel_clicked();

private:
    Ui::AddAirplaneDialog *ui;
};

#endif // ADDAIRPLANEDIALOG_H
