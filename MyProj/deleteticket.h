#ifndef DELETETICKET_H
#define DELETETICKET_H

#include <QDialog>

namespace Ui {
class deleteTicket;
}

class deleteTicket : public QDialog
{
    Q_OBJECT

public:
    explicit deleteTicket(QWidget *parent = nullptr);
    ~deleteTicket();

private:
    Ui::deleteTicket *ui;
};

#endif // DELETETICKET_H
