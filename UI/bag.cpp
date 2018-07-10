#include "bag.h"
#include "ui_bag.h"

Bag::Bag(QWidget *parent,QString res) :
    QWidget(parent),
    ui(new Ui::Bag)
{
    ui->setupUi(this);
    backX = 0;
    scene = res;
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setGeometry(backX, 120, 380,440);
    initTimer();
    loadImage();
}

void Bag::loadImage()
{
    backGround.load(":/menuZ/menu/bag_back_"+scene+".png");
    stellball.load(":/bag/prop/stellball_bag.png");
    stick.load(":/bag/prop/stick_bag.png");
}

void Bag::initTimer()
{
    timerShow = new QTimeLine(500, this);
    timerShow->setFrameRange(0,100);
    timerShow->setCurveShape(QTimeLine::LinearCurve);
    timerShow->setUpdateInterval(5);
    connect(timerShow,SIGNAL(frameChanged(int)),this,SLOT(bagShow()));

    timerHide = new QTimeLine(500, this);
    timerHide->setFrameRange(0,100);
    timerHide->setCurveShape(QTimeLine::LinearCurve);
    timerHide->setUpdateInterval(5);
    connect(timerHide,SIGNAL(frameChanged(int)),this,SLOT(bagHide()));
}

void Bag::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawImage( 0, -80, backGround);
}

void Bag::bagShow()
{
    if(backX < -5)
    {
        backX += 5;
        this->move(backX, 120);
    }
}

void Bag::bagHide()
{
    if(backX > -345)
    {
        backX  -= 5;
        this->move(backX, 120);
    }
    if(backX <= -345)
    {

    }
}

void Bag::closeEvent(QCloseEvent *e)
{

}

void Bag::enterEvent(QEvent *e)
{
    if(timerShow->state() == QTimeLine::Running)
    {
        timerShow->stop();
    }
    if(timerHide->state() == QTimeLine::Running)
    {
        timerHide->stop();
    }
    timerShow->start();
}

void Bag::leaveEvent(QEvent *e)
{
    if(timerShow->state() == QTimeLine::Running)
    {
        timerShow->stop();
    }
    if(timerHide->state() == QTimeLine::Running)
    {
        timerHide->stop();
    }
    timerHide->start();
}

Bag::~Bag()
{
    delete ui;
}
