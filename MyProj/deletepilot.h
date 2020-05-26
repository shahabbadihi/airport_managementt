#ifndef DELETEEMP_H
#define DELETEEMP_H

#include <QDialog>

namespace Ui {
class deleteEmp;
}

class deleteEmp : public QDialog
{
    Q_OBJECT

public:
    explicit deleteEmp(QWidget *parent = nullptr);
    ~deleteEmp();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::deleteEmp *ui;
};

#endif // DELETEEMP_H
