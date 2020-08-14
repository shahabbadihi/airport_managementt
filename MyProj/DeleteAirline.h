#ifndef DELETEAIRLINE_H
#define DELETEAIRLINE_H

#include <QDialog>

namespace Ui {
class DeleteAirline;
}

class DeleteAirline : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteAirline(QWidget *parent = nullptr);
    ~DeleteAirline();

private slots:
    void on_btnCancel_clicked();

    void on_btnSubmit_clicked();

private:
    Ui::DeleteAirline *ui;
};

#endif // DELETEAIRLINE_H
