#ifndef DELETEPILOT_H
#define DELETEPILOT_H

#include <QDialog>

namespace Ui {
class DeletePilot;
}

class DeletePilot : public QDialog
{
    Q_OBJECT

public:
    explicit DeletePilot(QWidget *parent = nullptr);
    ~DeletePilot();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::DeletePilot *ui;
};

#endif // DELETEPILOT_H
