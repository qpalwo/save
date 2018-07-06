#include "menuwidget.h"
#include "ui_menuwidget.h"

menuwidget::menuwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuwidget)
{
    ui->setupUi(this);
    backX = 0;

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setGeometry(backX,0,960,720);

    loadImage();


}

void menuwidget::loadImage()
{
    backGround.load(":/menuZ/menu/menu_background.png");
    acheive.load(":/menuZ/menu/menu_achieve_1.png");
}

void menuwidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.drawImage(0, 0,backGround);
    painter.drawPixmap(100, 200, 160, 50, acheive);
}

void menuwidget::mousePressEvent(QMouseEvent *e)
{

}

void menuwidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void menuwidget::enterEvent(QEvent *e)
{

}

void menuwidget::leaveEvent(QEvent *e)
{

}
menuwidget::~menuwidget()
{
    delete ui;
}
