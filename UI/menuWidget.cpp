#include "menuwidget.h"
#include "ui_menuwidget.h"

menuwidget::menuwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuwidget)
{
    ui->setupUi(this);

    backX = -350;
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setGeometry(backX, 120, 380, 440);
    initbutton();
    initTimer();

    loadImage();
}

void menuwidget::loadImage()
{
    backGround.load(":/menuZ/menu/menu_background.png");
    setBackGround.load(":/menuZ/menu/set_background.png");
}

void menuwidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawImage( 0, -80, backGround);
}

void menuwidget::initbutton()
{
    achieve = new OpenPageButton("", "menu_achieve",this);
    bag = new OpenPageButton("", "menu_bag", this);
    map = new OpenPageButton("", "menu_map", this);
    read = new OpenPageButton("", "menu_read", this);
    save = new OpenPageButton("", "menu_save", this);
    set = new OpenPageButton("", "menu_set", this);

    myLayout = new QGridLayout;

    myLayout->addWidget(achieve,1,1,Qt::Alignment());
    myLayout->addWidget(bag,2,2,Qt::Alignment());
    myLayout->addWidget(map,3,2,Qt::Alignment());
    myLayout->addWidget(read,2,1,Qt::Alignment());
    myLayout->addWidget(save,3,1,Qt::Alignment());
    myLayout->addWidget(set,1,2,Qt::Alignment());

    myLayout->setHorizontalSpacing(30);
    myLayout->setVerticalSpacing(0);
    myLayout->setContentsMargins(25,100,60,100);

    this->setLayout(myLayout);

    connect(achieve, SIGNAL(clicked()),this,SLOT(onAchieveClicked()));
    connect(bag, SIGNAL(clicked()),this,SLOT(onBagClicked()));
    connect(map, SIGNAL(clicked()),this,SLOT(onMapClicked()));
    connect(read, SIGNAL(clicked()),this,SLOT(onReadClicked()));
    connect(save, SIGNAL(clicked()),this,SLOT(onSaveClicked()));
    connect(set, SIGNAL(clicked()),this,SLOT(onSetClicked()));
}

void menuwidget::onAchieveClicked()
{

}

void menuwidget::onBagClicked()
{

}

void menuwidget::onMapClicked()
{

}

void menuwidget::onReadClicked()
{

}

void menuwidget::onSaveClicked()
{

}

void menuwidget::onSetClicked()
{

}

void menuwidget::initTimer()
{
    timerShow = new QTimeLine(500, this);
    timerShow->setFrameRange(0,100);
    timerShow->setCurveShape(QTimeLine::LinearCurve);
    timerShow->setUpdateInterval(5);
    connect(timerShow,SIGNAL(frameChanged(int)),this,SLOT(menuShow()));

    timerHide = new QTimeLine(500, this);
    timerHide->setFrameRange(0,100);
    timerHide->setCurveShape(QTimeLine::LinearCurve);
    timerHide->setUpdateInterval(5);
    connect(timerHide,SIGNAL(frameChanged(int)),this,SLOT(menuHide()));

}

void menuwidget::menuShow()
{
    if(backX < -5)
    {
        backX += 5;
        this->move(backX, 120);
    }
}

void menuwidget::menuHide()
{
    if(backX > -345)
    {
        backX  -= 5;
        this->move(backX, 120);
    }
}

void menuwidget::enterEvent(QEvent *e)
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

void menuwidget::leaveEvent(QEvent *e)
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
menuwidget::~menuwidget()
{
    delete ui;
}
