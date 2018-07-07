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
    acheive = new OpenPageButton("", "menu_acheive",this);
    bag = new OpenPageButton("", "menu_bag", this);
   // map = new OpenPageButton("", "menu_map", this);
   // read = new OpenPageButton("", "menu_read", this);
    //save = new OpenPageButton("", "menu_save", this);
   // set = new OpenPageButton("", "menu_set", this);

    acheive->setGeometry(rect().x(),rect().y(), 130, 50);
    bag->setGeometry(rect().x()-200, rect().y()-100, 130, 50);

    acheive->show();
    bag->show();
}

void menuwidget::enterEvent(QEvent *e)
{
    if (backX == -340)
    {
        backX = 0;
        this->setGeometry(backX,120,380,440);
        //initbutton();
    }
    update();
}

void menuwidget::leaveEvent(QEvent *e)
{
    if (backX == 0)
    {
        backX = -340;
        this->setGeometry(backX,120,380,440);
        //initbutton();
    }
    update();
}
menuwidget::~menuwidget()
{
    delete ui;
}
