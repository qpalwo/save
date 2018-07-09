#ifndef BEGINING_H
#define BEGINING_H

#include <QWidget>

namespace Ui {
class Begining;
}

class Begining : public QWidget
{
    Q_OBJECT

public:
    explicit Begining(QWidget *parent = 0);
    ~Begining();

private:
    Ui::Begining *ui;
};

#endif // BEGINING_H
