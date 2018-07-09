#ifndef KEEPMOVING_H
#define KEEPMOVING_H

#include <QWidget>

namespace Ui {
class KeepMoving;
}

class KeepMoving : public QWidget
{
    Q_OBJECT

public:
    explicit KeepMoving(QWidget *parent = 0);
    ~KeepMoving();

private:
    Ui::KeepMoving *ui;
};

#endif // KEEPMOVING_H
