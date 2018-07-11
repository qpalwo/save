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

int GameWorld::getGameHard() {
	return gameHard;
}

void GameWorld::showAchieve() {
	UiManager::getInstance()->openAchieve();
}

void GameWorld::showGameMap() {
	UiManager::getInstance()->openGameMap();
}

void GameWorld::hideAchieve() {
	UiManager::getInstance()->closeAchieve();
}

void GameWorld::save() {
	m_achieve.save();
}

void GameWorld::load() {

}
void GameWorld::quitGame() {
	GameWorld::save();
	qApp->quit();
}

bool* GameWorld::getAllAchieve() {
	return m_achieve.getAllAchieve();
}

void GameWorld::addAchieve(int num) {
	m_achieve.addAchieve(num);
}

GameWorld::GameWorld(QObject *parent) : QObject(parent) {
	GameWorld::load();
}

GameWorld* GameWorld::Instance = new GameWorld();


void GameWorld::fromMainToBegining() {
	UiManager::getInstance()->openBegining();
	UiManager::getInstance()->closeMainPage();
}

void GameWorld::fromBeginingToRuinsCity() {
	UiManager::getInstance()->openRuins();
	UiManager::getInstance()->closeBegining();
}

void GameWorld::showSaveAndLoad() {
	UiManager::getInstance()->openSaveAndLoad();
}

void GameWorld::beginSmellCollect() {
	UiManager::getInstance()->openSunSmellCollect(gameHard);
}

void GameWorld::beginAvoidStorm() {
	UiManager::getInstance()->openAvoidStorm(gameHard);
}

void GameWorld::beginKeepMoving() {
	UiManager::getInstance()->openKeepMoving(gameHard);
}

void GameWorld::beginBurnBook() {
	UiManager::getInstance()->openBurnBook(gameHard);
}

QString* GameWorld::getAllSaves() {
	return savesPath;
}

void GameWorld::addSaves(QString path, int position) {
	savesPath[position] = path;
}

GameWorld* GameWorld::getInstance() {
	return Instance;
}

void GameWorld::setVolume(int v){
    volume = v;
}

int GameWorld::getVolume(){
    return volume;
}
GameWorld::~GameWorld() {
	GameWorld::save();
}






AchieveData::AchieveData() {
	AchieveData::load();
}


void AchieveData::addAchieve(int num) {
	AchieveData::m_achieves[num] = true;
	AchieveData::save();
}

void AchieveData::save() {
	QJsonArray achieveArr;
	for (bool i : m_achieves) {
		achieveArr.append(i);
	}
	QJsonDocument document;
	document.setArray(achieveArr);
	QByteArray bytearr = document.toJson(QJsonDocument::Compact);
	QtConcurrent::run(saveToDisk, bytearr, QString("userInfo/achieve.info"));
}



void AchieveData::load() {
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

bool * AchieveData::getAllAchieve() {
	for (int i = 0; i < 7; i++) {
		m_achieves[i] = true;
	}
	return m_achieves;
}

AchieveData::~AchieveData() {
	AchieveData::save();
}
