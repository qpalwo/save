#include "sceneforest.h"
#include "ui_sceneforest.h"

SceneForest::SceneForest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneForest)
{
    ui->setupUi(this);
}

void SceneForest::paintEvent(QPaintEvent * e) {

}

SceneForest::~SceneForest()
{
    delete ui;
}
