#ifndef SCENESNOW_H
#define SCENESNOW_H

#include <QWidget>

namespace Ui {
class SceneSnow;
}

class SceneSnow : public QWidget
{
    Q_OBJECT

public:
    explicit SceneSnow(QWidget *parent = 0);
    ~SceneSnow();

private:
    Ui::SceneSnow *ui;
};

#endif // SCENESNOW_H
