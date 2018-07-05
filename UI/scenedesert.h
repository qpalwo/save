#ifndef SCENEDESERT_H
#define SCENEDESERT_H

#include <QWidget>

namespace Ui {
class SceneDesert;
}

class SceneDesert : public QWidget
{
    Q_OBJECT

public:
    explicit SceneDesert(QWidget *parent = 0);
    ~SceneDesert();
	void paintEvent(QPaintEvent * e);

private:
    Ui::SceneDesert *ui;
};

#endif // SCENEDESERT_H
