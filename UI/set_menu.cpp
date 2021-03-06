#include "set_menu.h"
#include "ui_set_menu.h"

set_menu::set_menu(QString res, QWidget *menu, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::set_menu)
{
    ui->setupUi(this);

    menu->hide();
    backX = 0;
    backGround.load(":/menuZ/menu/set_background_"+res+".png");
    back = new OpenPageButton("","set_back_"+res,this);
    back->setGeometry(30,260,70,70);
    back->show();
    this->setGeometry(backX,120,380,440);

    initTimer();
    newMenu = new menuwidget(res,parentWidget());

    connect(back,SIGNAL(clicked()),this,SLOT(onBackClicked()));

    setMouseTracking(true);

    volume = GameWorld::getInstance()->getVolume();
    volumeShow = volume*2.35;

    volumeBack.load(":/menuZ/menu/set_sound_"+res+"_1.png");
    volumeCover.load(":/menuZ/menu/set_volume_"+res+"_2.png");
    volumeSetting = new QLabel(this);
    volumeSetting->setPixmap(volumeCover);
    volumeSetting->setGeometry(25,150,60+volumeShow,50);
}

void set_menu::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(0,-80,backGround);
    painter.drawImage(25,150,volumeBack);

}

void set_menu::initTimer()
{
    timerShow = new QTimeLine(500, this);
    timerShow->setFrameRange(0,100);
    timerShow->setCurveShape(QTimeLine::LinearCurve);
    timerShow->setUpdateInterval(5);
    connect(timerShow,SIGNAL(frameChanged(int)),this,SLOT(setShow()));

    timerHide = new QTimeLine(500, this);
    timerHide->setFrameRange(0,100);
    timerHide->setCurveShape(QTimeLine::LinearCurve);
    timerHide->setUpdateInterval(5);
    connect(timerHide,SIGNAL(frameChanged(int)),this,SLOT(setHide()));
}

void set_menu::setShow()
{
    if(backX < -5)
    {
        backX += 5;
        this->move(backX, 120);
    }
}

void set_menu::setHide()
{
    if(backX > -345)
    {
        backX  -= 5;
        this->move(backX, 120);
    }
    if(backX <= -345)
    {
        this->close();
        newMenu->show();
    }
}

void set_menu::closeEvent(QCloseEvent *e)
{
    if(timerShow->state() == QTimeLine::Running)
    {
        timerShow->stop();
    }
    if(timerHide->state() == QTimeLine::Running)
    {
        timerHide->stop();
    }
}

void set_menu::enterEvent(QEvent *e)
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

void set_menu::leaveEvent(QEvent *e)
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

void set_menu::mouseMoveEvent(QMouseEvent *event){
    mouse = event->pos();
}

void set_menu::mousePressEvent(QMouseEvent *event){
    if(mouse.x()>=85&&mouse.x()<=320)
        press = true;
    else press = false;
}

void set_menu::mouseReleaseEvent(QMouseEvent *event){
    if(press)
    {
        if(mouse.x()<=85) volume = 0;
        else
        {
            if(mouse.x()>=320) volume = 100;
            else volume = (mouse.x()-85)/2.35;
        }
        GameWorld::getInstance()->setVolume(volume);
        volume = GameWorld::getInstance()->getVolume();
        volumeShow = volume*2.35;
        volumeSetting->setGeometry(25,150,60+volumeShow,50);
    }
}
void set_menu::onBackClicked(){
    this->close();
    newMenu->show();
}
set_menu::~set_menu()
{
    delete ui;
}
