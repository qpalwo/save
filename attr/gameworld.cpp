#include "gameworld.h"
#include "UI/UiManager.h"
#include "player.h"

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
	newPlayer(hard);
}

int GameWorld::getGameHard() {
	return gameHard;
}

void GameWorld::newPlayer(int hard) {
	int id = 0;
	for (QString s : savesPath) {
		if (s.length() > 1) id++;
	}
	if (id > 5) {
		id = 0;
	}
	savesPath[id] = "userInfo/" + QTime::currentTime().toString();
	Player::getInstance()->newPlayer(savesPath[id], hard);
}

void GameWorld::loadPlayer(int id) {
	Player::getInstance()->load(savesPath[id]);
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


void GameWorld::changeStaus(bool a, bool b, bool c, bool d) {

}

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

void GameWorld::closeBurnBook() {
	UiManager::getInstance()->closeBurnBook();
	UiManager::getInstance()->informeSnow();
}

void GameWorld::closeAvoidStorm() {
	UiManager::getInstance()->closeAvoidStorm();
	UiManager::getInstance()->informeDesert();
}

void GameWorld::closeCollectSmell() {
	UiManager::getInstance()->closeSunSmellCollect();
	UiManager::getInstance()->informeForest();
}

void GameWorld::closeKeepMoving() {
	UiManager::getInstance()->closeKeepMoving();
	UiManager::getInstance()->informeRuins();
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


GameWorld::~GameWorld() {
	GameWorld::save();
}






AchieveData::AchieveData() {
	AchieveData::load();
}


void AchieveData::addAchieve(int num) {
	if(num - 1 >= 0 && num - 1 < 23)
		AchieveData::m_achieves[num - 1] = true;
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
	return m_achieves;
}

AchieveData::~AchieveData() {
	AchieveData::save();
}