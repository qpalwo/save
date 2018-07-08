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

namespace Ui {
class menuwidget;
}

class menuwidget : public QWidget
{
    Q_OBJECT

public:
    explicit menuwidget(QWidget *parent = 0);
    ~menuwidget();

private:
    Ui::menuwidget *ui;

    QImage backGround;
    QImage setBackGround;

    OpenPageButton *achieve;
    OpenPageButton *bag;
    OpenPageButton *map;
    OpenPageButton *read;
    OpenPageButton *save;
    OpenPageButton *set;

    QGridLayout *myLayout;
    QTimeLine *timerShow;
    QTimeLine *timerHide;

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
    void onReadClicked();
    void onSaveClicked();
    void onSetClicked();
};

#endif // MENUWIDGET_H
