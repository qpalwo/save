#ifndef BAG_H
#define BAG_H

#include <QWidget>

namespace Ui {
class Bag;
}

class Bag : public QWidget
{
    Q_OBJECT

public:
    explicit Bag(QWidget *parent = nullptr);
    ~Bag();

private:
    Ui::Bag *ui;
};

#endif // BAG_H
