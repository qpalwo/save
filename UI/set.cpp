#include "set.h"
#include "ui_set.h"

set::set(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::set)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    back.load(":/setting/back.png");
    volumeBack.load(":/setting/set_sound_1.png");
    volumeCover.load(":/setting/set_volume_2.png");
    backButton = new OpenPageButton(this, "/menuZ/menu/", "set_back_snow");
    backButton->setGeometry(830, 570, 70, 70);
    connect(backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));

    setMouseTracking(true);

    volume = GameWorld::getInstance()->getVolume();
    volumeShow = volume*2.35;

    volumeSetting = new QLabel(this);
    volumeSetting->setPixmap(volumeCover);
    volumeSetting->setGeometry(530,300,60+volumeShow,50);
}

void set::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,back);
    painter.drawImage(530,300,volumeBack);
    //painter.drawImage(530,300,volumeCover,0,0,60+volumeShow,50);
    //painter.drawText(100,50,QString::number(volume));
}

void set::mouseMoveEvent(QMouseEvent *event){
    mouse = event->pos();
}

void set::mousePressEvent(QMouseEvent *event){
    if(mouse.x()>=605&&mouse.x()<=840&&mouse.y()>=327&&mouse.y()<=337)
        press = true;
    else press = false;
}

void set::mouseReleaseEvent(QMouseEvent *event){
    s = QString::number(mouse.x())+" "+QString::number(mouse.y());
    if(press)
    {
        if(mouse.x()<=605) volume = 0;
        else
        {
            if(mouse.x()>=840) volume = 100;
            else volume = (mouse.x()-605)/2.35;
        }
        GameWorld::getInstance()->setVolume(volume);
        volume = GameWorld::getInstance()->getVolume();
        volumeShow = volume*2.35;
        volumeSetting->setGeometry(530,300,60+volumeShow,50);
    }
}

void set::onBackClicked(){
    close();
    deleteLater();
}

set::~set()
{
    delete ui;
}
