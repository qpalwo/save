#include "gameworld.h"
#include "UI/UiManager.h"

void saveToDisk(QByteArray content, QString path) {
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly)) {
		qDebug() << "save unsuccessful";
	}
	else {
		if (file.write(content) > 0) {
			qDebug() << "save successful";
			file.close();
		}
		else {
			qDebug() << "save unsuccessful";
		}	
	}
}

QByteArray loadFromDisk(QString path) {
	QFile file(path);
	if (file.exists()) {
		if (file.open(QIODevice::ReadOnly)) {
			QByteArray end = file.readAll();
			file.close();
			return end;
		}
		else {
			qDebug() << "load unsuccessful";
			return NULL;
		}
	}
	else {
		qDebug() << "load unsuccessful";
		return NULL;
	}
}

void GameWorld::setGameHard(int hard) {
	this->gameHard = hard;
}

void GameWorld::save() {

}

void GameWorld::load() {

}
void GameWorld::quitGame() {
	GameWorld::save();
	qApp->quit();
}

GameWorld::GameWorld(QObject *parent) : QObject(parent)
{

}

GameWorld* GameWorld::Instance = new GameWorld();

void GameWorld::addAchieve(int num) {
	m_achieve.addAchieve(num);
}

void GameWorld::fromMainToBegining() {
	UiManager::getInstance()->openBegining();
	UiManager::getInstance()->closeMainPage();
}

GameWorld* GameWorld::getInstance() {
	return Instance;
}


Achieve::Achieve() {
	load();
}


void Achieve::addAchieve(int num) {
	Achieve::m_achieves[num] = true;
	Achieve::save();
}

void Achieve::save() {
	QJsonArray achieveArr;
	for (bool i : m_achieves) {
		achieveArr.append(i);
	}
	QJsonDocument document;
	document.setArray(achieveArr);
	QByteArray bytearr = document.toJson(QJsonDocument::Compact);
	QtConcurrent::run(saveToDisk, bytearr, QString("userInfo/achieve.info"));
}



void Achieve::load() {
	QJsonDocument document = QJsonDocument::fromJson(loadFromDisk(QString("userInfo/achieve.info")));
	if (!document.isNull()) {
		if (document.isArray()) {
			QJsonArray arr = document.array();
			int size = arr.size();
			for (int i = 0; i < size; i++) {
				m_achieves[i] = arr.at(i).toBool();
			}
		}
	}
}

Achieve::~Achieve() {

}