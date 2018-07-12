#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include "attr/player.h"
#include <QImage>
#include <QPainter>
#include "openpagebutton.h"
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>

namespace Ui {
class GameMap;
}

class GameMap : public QWidget
{
    Q_OBJECT

public:
    explicit GameMap(bool, QWidget *parent = 0);
    ~GameMap();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::GameMap *ui;
	bool *m_map;

    QImage initial;
    QImage desert;
    QImage forest;
    QImage ruins;
    QImage snow;
    QPixmap small;
    QLabel *myLabel;

    QPoint mouse;
    int posX;
    int posY;
    int id = 0;
	bool m_is;

    OpenPageButton *backButton;

    void loadImage();
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
	void checkMap();

private slots:
    void onBackClicked();
};

#endif // GAMEMAP_H
