#ifndef BAG_H
#define BAG_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QGridLayout>
#include <QTimeLine>
#include <QCloseEvent>
#include <QString>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include "attr/player.h"

class menuwidget;
#include "menuWidget.h"

namespace Ui {
class Bag;
}

class Bag : public QWidget
{
    Q_OBJECT

public:
    Bag(QString res,QWidget *menu,QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *e);
    ~Bag();

private:
    Ui::Bag *ui;

    QImage backGround;
    QString scene;

    QPixmap prop1;
    QPixmap prop2;
    QPixmap prop3;
    QPixmap prop4;
    QPixmap prop5;
    QPixmap prop6;
    QPixmap prop7;
    QPixmap prop8;
    QPixmap prop9;
    QPixmap prop10;
    QPixmap prop11;
    QPixmap prop12;

    QPoint mouse;

    QTimeLine *timerShow;
    QTimeLine *timerHide;

    menuwidget *newMenu;

    Player *player;
    int num[12];
    QString s[12];

    int backX;

    void paintEvent(QPaintEvent *e);
    void loadImage();
    void leaveEvent(QEvent *e);
    void enterEvent(QEvent *e);
    void initTimer();

private slots:
    void bagShow();
    void bagHide();

};

#endif // BAG_H
