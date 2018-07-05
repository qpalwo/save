#ifndef SCENEFOREST_H
#define SCENEFOREST_H

#include <QWidget>

namespace Ui {
class SceneForest;
}

class SceneForest : public QWidget
{
    Q_OBJECT

public:
    explicit SceneForest(QWidget *parent = 0);
    ~SceneForest();
	void paintEvent(QPaintEvent * e);

private:
    Ui::SceneForest *ui;
};

#endif // SCENEFOREST_H
