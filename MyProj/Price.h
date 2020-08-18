
#ifndef PRICE_H
#define PRICE_H
#include <QException>
#include <QString>

class Price
{
private:
    int64_t amount;
public:
    Price(int64_t a = 0)
    {
        if (a < 0)
            throw QException();
        this->amount = a;
    }

    QString toString()
    {
        QString dollar = QString::number(amount / 100);
        QString cent = QString::number(amount % 100);
        return dollar + "." + cent.size() == 1 ? "0" : "" + cent;
    }
};

#endif // PRICE_H
