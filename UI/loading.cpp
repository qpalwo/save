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

void Loading::on_pushButton_5_clicked() {
	UiManager::getInstance()->showSunSmellCollect();
}

void Loading::on_pushButton_6_clicked() {
	UiManager::getInstance()->showAvoidStorm();
}

void Loading::on_pushButton_7_clicked() {
	UiManager::getInstance()->showRuins();
}

void Loading::on_pushButton_8_clicked() {
	UiManager::getInstance()->showSnow();
}

void Loading::on_pushButton_9_clicked() {
	UiManager::getInstance()->showKeepMoving();
}

