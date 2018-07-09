#ifndef ACHIEVE_H
#define ACHIEVE_H

#include <QWidget>

namespace Ui {
class Achieve;
}

class Achieve : public QWidget
{
    Q_OBJECT

public:
    explicit Achieve(QWidget *parent = 0);
    ~Achieve();

private:
    Ui::Achieve *ui;
};

#endif // ACHIEVE_H
