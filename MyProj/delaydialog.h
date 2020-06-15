#ifndef DELAYDIALOG_H
#define DELAYDIALOG_H

#include <QDialog>

namespace Ui {
class DelayDialog;
}

class DelayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelayDialog(QWidget *parent = nullptr);
    ~DelayDialog();

    qint64 milli_delay();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DelayDialog *ui;
};

#endif // DELAYDIALOG_H
