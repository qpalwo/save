#include "set.h"
#include "ui_set.h"

set::set(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::set)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    back.load(":/setting/back.png");
    backButton = new OpenPageButton(this, "/menuZ/menu/", "set_back_snow");
    backButton->setGeometry(830, 570, 70, 70);
    connect(backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));
}

void set::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,back);
}

void set::onBackClicked(){
    close();
}

set::~set()
{
    delete ui;
}
