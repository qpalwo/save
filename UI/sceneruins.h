#ifndef SCENERUINS_H
#define SCENERUINS_H

#include <QWidget>

namespace Ui {
class SceneRuins;
}

class SceneRuins : public QWidget
{
    Q_OBJECT

public:
    explicit SceneRuins(QWidget *parent = 0);
    ~SceneRuins();

private:
    Ui::SceneRuins *ui;
};

#endif // SCENERUINS_H
