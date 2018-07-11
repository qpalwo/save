#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include "attr/player.h"
#include <QImage>
#include <QPainter>
#include "openpagebutton.h"

namespace Ui {
class GameMap;
}

class GameMap : public QWidget
{
    Q_OBJECT

public:
    explicit GameMap(QWidget *parent = 0);
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

    OpenPageButton *backButton;

    void loadImage();

private slots:
    void onBackClicked();
};

#endif // GAMEMAP_H
