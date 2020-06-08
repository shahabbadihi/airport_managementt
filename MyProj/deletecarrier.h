#ifndef DELETECARRIER_H
#define DELETECARRIER_H

#include <QDialog>

namespace Ui {
class deleteCarrier;
}

class deleteCarrier : public QDialog
{
    Q_OBJECT

public:
    explicit deleteCarrier(QWidget *parent = nullptr);
    ~deleteCarrier();

private slots:
    void on_btnCancel_clicked();

    void on_btnSubmit_clicked();

private:
    Ui::deleteCarrier *ui;
};

#endif // DELETECARRIER_H
