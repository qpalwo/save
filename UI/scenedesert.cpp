#include "scenedesert.h"
#include "ui_scenedesert.h"

SceneDesert::SceneDesert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneDesert)
{
    ui->setupUi(this);
}

void SceneDesert::paintEvent(QPaintEvent * e) {

}

SceneDesert::~SceneDesert()
{
    delete ui;
}
