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

private:
    Ui::deleteCarrier *ui;
};

#endif // DELETECARRIER_H
