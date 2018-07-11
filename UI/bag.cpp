#include "bag.h"
#include "ui_bag.h"

Bag::Bag(QString res,QWidget *menu,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bag)
{
    ui->setupUi(this);
    backX = 0;
    menu->hide();
    scene = res;
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setGeometry(backX, 120, 380,440);
    initTimer();
    loadImage();
    newMenu = new menuwidget(scene,parentWidget());

    player = Player::getInstance();

    for(int i = 0;i<12;i++)
    {
        num[i] = (player->getBagThing() + i)->num;
        s[i] = QString::number(num[i],10);
    }

    setMouseTracking(true);

    explain = new QLabel (this);


}

void Bag::loadImage()
{
    backGround.load(":/menuZ/menu/bag_back_"+scene+".png");
    prop1.load(":/bag/prop/1_bag.png");
    prop2.load(":/bag/prop/2_bag.png");
    prop3.load(":/bag/prop/3_bag.png");
    prop4.load(":/bag/prop/4_bag.png");
    prop5.load(":/bag/prop/5_bag.png");
    prop6.load(":/bag/prop/6_bag.png");
    prop7.load(":/bag/prop/7_bag.png");
    prop8.load(":/bag/prop/8_bag.png");
    prop9.load(":/bag/prop/9_bag.png");
    prop10.load(":/bag/prop/10_bag.png");
    prop11.load(":/bag/prop/11_bag.png");
    prop12.load(":/bag/prop/12_bag.png");


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
    painter.drawPixmap(65, 133, 31,52,prop1);
    painter.drawPixmap(130,137,35,35,prop2);
    painter.drawPixmap(180,120,prop3);
    painter.drawPixmap(245,130,prop4);
    painter.drawPixmap(52,205,60,40,prop5);
    painter.drawPixmap(130,200,40,50,prop6);
    painter.drawPixmap(200,195,26,60,prop7);
    painter.drawPixmap(253,197,54,56,prop8);
    painter.drawPixmap(60,265,40,50,prop9);
    painter.drawPixmap(130,262,39,58,prop10);
    painter.drawPixmap(190,270,prop11);
    painter.drawPixmap(263,268,prop12);

    painter.drawText(93,185,s[0]);
    painter.drawText(160,185,s[1]);
    painter.drawText(228,185,s[2]);
    painter.drawText(295,185,s[3]);
    painter.drawText(95,252,s[4]);
    painter.drawText(160,252,s[5]);
    painter.drawText(228,252,s[6]);
    painter.drawText(295,252,s[7]);
    painter.drawText(95,320,s[8]);
    painter.drawText(160,320,s[9]);
    painter.drawText(228,320,s[10]);
    painter.drawText(295,320,s[11]);


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
        this->close();
        newMenu->show();
    }
}

void Bag::closeEvent(QCloseEvent *e)
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

void Bag::mouseMoveEvent(QMouseEvent *event){
    mouse = event->pos();

    int x[5]={53, 112, 178, 246, 309};
    int y[4]={130, 189, 258, 325};
    posX = mouse.x();
    posY = mouse.y();
    id = 0;
    if(posX>x[0]&&posX<x[1]&&posY>y[0]&&posY<y[1])  id = 1;
    if(posX>x[1]&&posX<x[2]&&posY>y[0]&&posY<y[1])  id = 2;
    if(posX>x[2]&&posX<x[3]&&posY>y[0]&&posY<y[1])  id = 3;
    if(posX>x[3]&&posX<x[4]&&posY>y[0]&&posY<y[1])  id = 4;
    if(posX>x[0]&&posX<x[1]&&posY>y[1]&&posY<y[2])  id = 5;
    if(posX>x[1]&&posX<x[2]&&posY>y[1]&&posY<y[2])  id = 6;
    if(posX>x[2]&&posX<x[3]&&posY>y[1]&&posY<y[2])  id = 7;
    if(posX>x[3]&&posX<x[4]&&posY>y[1]&&posY<y[2])  id = 8;
    if(posX>x[0]&&posX<x[1]&&posY>y[2]&&posY<y[3])  id = 9;
    if(posX>x[1]&&posX<x[2]&&posY>y[2]&&posY<y[3])  id = 10;
    if(posX>x[2]&&posX<x[3]&&posY>y[2]&&posY<y[3])  id = 11;
    if(posX>x[3]&&posX<x[4]&&posY>y[2]&&posY<y[3])  id = 12;

    if (id != 0){
    propExplain.load(":/bag/prop/"+QString::number(id,10)+"_explain.png");
    explain->setPixmap(propExplain);
    switch (id) {
    case 1:
        explain->setGeometry(56,193,251,123);
        break;
    case 2:
        explain->setGeometry(114,193,251,123);
        break;
    case 3:
        explain->setGeometry(56,193,251,123);
        break;
    case 4:
        explain->setGeometry(114,193,251,123);
        break;
    case 5:
        explain->setGeometry(56,260,251,123);
        break;
    case 6:
        explain->setGeometry(114,260,251,123);
        break;
    case 7:
        explain->setGeometry(56,260,251,123);
        break;
    case 8:
        explain->setGeometry(114,260,251,123);
        break;
    case 9:
        explain->setGeometry(56,135,251,123);
        break;
    case 10:
        explain->setGeometry(114,135,251,123);
        break;
    case 11:
        explain->setGeometry(56,135,251,123);
        break;
    case 12:
        explain->setGeometry(114,135,251,123);
        break;
    default:
        break;
    }
}
}


Bag::~Bag()
{
    delete ui;
}
