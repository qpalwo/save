#ifndef OPEN_H
#define OPEN_H

#include <QWidget>

namespace Ui {
class open;
}

class open : public QWidget
{
    Q_OBJECT

public:
    explicit open(QWidget *parent = 0);
    void paintEvent(QPaintEvent * e);
    ~open();

private:
    Ui::open *ui;
};

#endif // OPEN_H
