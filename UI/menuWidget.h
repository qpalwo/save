#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QImage>
#include <QPoint>
#include <QPushButton>
#include "openpagebutton.h"
#include <QGridLayout>
#include <QTimeLine>
#include <QString>
#include "attr/gameworld.h"

class Bag;
#include "bag.h"

class set_menu;
#include "set_menu.h"

namespace Ui {
class menuwidget;
}

class menuwidget : public QWidget
{
    Q_OBJECT

public:
    menuwidget(QString res,QWidget *parent = 0);
    ~menuwidget();

private:
    Ui::menuwidget *ui;

    QImage backGround;
    QImage setBackGround;
    QString scene;

    OpenPageButton *achieve;
    OpenPageButton *bag;
    OpenPageButton *map;
    OpenPageButton *back;
    OpenPageButton *save;
    OpenPageButton *set;

    QGridLayout *myLayout;
    QTimeLine *timerShow;
    QTimeLine *timerHide;

    Bag *bagwidget;
    set_menu *setting;

    int backX;

    void loadImage();
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void initbutton();
    void initTimer();

private slots:
    void menuShow();
    void menuHide();
    void onAchieveClicked();
    void onBagClicked();
    void onMapClicked();
    void onBackClicked();
    void onSaveClicked();
    void onSetClicked();
};

#endif // MENUWIDGET_H
