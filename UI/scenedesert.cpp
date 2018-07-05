#include "scenedesert.h"
#include "ui_scenedesert.h"

SceneDesert::SceneDesert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneDesert)
{
    ui->setupUi(this);
}

void SceneDesert::loadImage() {
	backGround.load(":/openRes/desert_1.png");
	earth.load(":/openRes/desert_2.png");

}

void SceneDesert::paintEvent(QPaintEvent * e) {
	QPainter painter(this);

	painter.drawImage(XX, YY, backGround);
	painter.drawImage(XX, YY, backGround);

}

SceneDesert::~SceneDesert()
{
    delete ui;
}
