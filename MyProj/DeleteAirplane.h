#ifndef DELETEAIRPLANE_H
#define DELETEAIRPLANE_H

#include <QDialog>

#include "AirplaneItemModel.h"

namespace Ui {
class DeleteAirplane;
}

class DeleteAirplane : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteAirplane(QWidget *parent = nullptr);
    ~DeleteAirplane();

private slots:
    void on_btnSubmit_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DeleteAirplane *ui;

    AirplaneItemModel * model;
};

#endif // DELETEAIRPLANE_H
