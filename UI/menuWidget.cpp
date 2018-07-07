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
    initbutton();

    loadImage();
}

void menuwidget::loadImage()
{
    backGround.load(":/menuZ/menu/menu_background.png");
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
    myLayout->addWidget(bag,1,2,Qt::Alignment());
    myLayout->addWidget(map,2,1,Qt::Alignment());
    myLayout->addWidget(read,2,2,Qt::Alignment());
    myLayout->addWidget(save,3,1,Qt::Alignment());
    myLayout->addWidget(set,3,2,Qt::Alignment());

    myLayout->setHorizontalSpacing(30);
    myLayout->setVerticalSpacing(0);
    myLayout->setContentsMargins(25,100,60,100);

    this->setLayout(myLayout);
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
