#ifndef SET_MENU_H
#define SET_MENU_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include "openpagebutton.h"
#include <QString>
#include <QTimeLine>
#include <QCloseEvent>
#include "attr/gameworld.h"
#include <QPoint>


class menuwidget;
#include "menuWidget.h"

namespace Ui {
class set_menu;
}

class set_menu : public QWidget
{
    Q_OBJECT

public:
    explicit set_menu(QString res,QWidget *menu,QWidget *parent = 0);
    void closeEvent(QCloseEvent *e);
    ~set_menu();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::set_menu *ui;

    QImage backGround;
    OpenPageButton* back;
    menuwidget *newMenu;

    QPoint mouse;
    QImage volumeBack;
    QPixmap volumeCover;
    QLabel *volumeSetting;
    bool press;
    int volume;
    int volumeShow;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    QTimeLine *timerShow;
    QTimeLine *timerHide;

    int backX;

    void initTimer();
    void leaveEvent(QEvent *e);
    void enterEvent(QEvent *e);

private slots:
    void onBackClicked();
    void setShow();
    void setHide();

};

#endif // SET_MENU_H
