#include "menuwidget.h"
#include "ui_menuwidget.h"

menuwidget::menuwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuwidget)
{
    ui->setupUi(this);
    backX = -340;

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setGeometry(backX,120,380,440);

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

    painter.drawImage(0, -80,backGround);
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
    if (backX == -340)
    {
        backX = 0;
        this->setGeometry(backX,120,380,440);
    }
    update();
}

void menuwidget::leaveEvent(QEvent *e)
{
    if (backX == 0)
    {
        backX = -340;
        this->setGeometry(backX,120,380,440);
    }
    update();
}
menuwidget::~menuwidget()
{
    delete ui;
}
