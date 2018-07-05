#include "loading.h"
#include "ui_loading.h"

Loading::Loading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
	setWindowFlag(Qt::FramelessWindowHint);
	backGif = new QMovie(":/openGif/letter_2.gif");
	ui->gifLabel->setMovie(backGif);
	backGif->start();
}

Loading::~Loading()
{
    delete ui;
}

void Loading::on_pushButton_clicked()
{
    UiManager::getInstance()->showMainWindow();
}

void Loading::on_pushButton_2_clicked()
{
	UiManager::getInstance()->showSceneDesert();
}

void Loading::on_pushButton_3_clicked()
{
	UiManager::getInstance()->showSceneForest();
}

void Loading::on_pushButton_4_clicked() {
	close();
}

