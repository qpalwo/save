#include "player.h"
#include "gameworld.h"
#include "UI/UiManager.h"

extern void saveToDisk(QByteArray content, QString path);

extern QByteArray loadFromDisk(QString path);


Player::Player(QObject *parent) : QObject(parent) {
	m_hard = GameWorld::getInstance()->getGameHard();
}

Player* Player::getInstance() {
	return Player::Instance;
}


Player* Player::Instance = new Player();

void Player::load(QString path) {
	m_path = path;
	QString loadPath = m_path + "_user.info";
	QJsonDocument document = QJsonDocument::fromJson(loadFromDisk(loadPath));
	if (!document.isNull()) {
		QString temp = document.toJson();
		QJsonObject obj = document.object();
		m_hard = obj.take("m_hard").toInt();
		m_power = obj.take("m_power").toInt();
		m_mood = obj.take("m_mood").toInt();
		m_id = obj.take("m_id").toInt();
		m_outScene = obj.take("m_outScene").toInt();
		QJsonArray mapArr = obj.take("m_map").toArray();
		for (int i = 0; i < 4; i++) {
			m_map[i] = mapArr.at(i).toBool();
		}
	}
	checkStaus();
	backBag.load(m_path);
	UiManager::getInstance()->loadScene(m_outScene);
}

void Player::newPlayer(QString path, int hard, int id) {
	backBag.newBag();
	m_id = id;
	m_path = path;
	m_mood = 80;
	m_power = 80;
	m_hard = hard;
	m_outScene = 3;
	save();
}

void Player::checkStaus() {
	if (m_mood <= 60) {
		m_staus[0] = true;
	}
	else {
		m_staus[0] = false;
	}
	if (m_power <= 50) {
		m_staus[1] = true;
	}
	else {
		m_staus[1] = false;
	}
	if (m_mood <= 20) {
		m_staus[2] = true;
	}
	else {
		m_staus[2] = false;
	}
	if (m_mood <= 20 && m_power <= 30) {
		m_staus[3] = true;
	}
	else {
		m_staus[3] = false;
	}
	GameWorld::getInstance()->changeStaus(m_staus[0], m_staus[1], m_staus[2], m_staus[3]);
}

void Player::changePower(int num) {
	Player::m_power = num;
	checkStaus();
}

void Player::changeMood(int num) {
	Player::m_mood = num;
	checkStaus();
}

BagThing *Player::getBagThing() {
	return backBag.getBagThing();
}

bool* Player::getMapStaus() {
	return m_map;
}

void Player::setMapStaus(int map) {
	if(map <= 4)
		m_map[map - 1] = false;
}

void Player::addBagThing(int num) {
	backBag.addBagThing(num);
}

void Player::useBagThing(int num) {
	backBag.useBagThing(num);
	UiManager::getInstance()->useThing(num);
}

bool* Player::nowStaus() {
	return m_staus;
}

void Player::setOutScene(int out) {
	m_outScene = out;
}

void Player::save() {
	backBag.save(m_path);
	QString savePath = m_path + "_user.info";

	QJsonObject saves;
	saves.insert("m_hard", m_hard);
	saves.insert("m_power", m_power);
	saves.insert("m_mood", m_mood);
	saves.insert("m_id", m_id);
	saves.insert("m_outScene", m_outScene);
	QJsonArray mapArr;
	for (bool i : m_map) {
		mapArr.append(i);
	}
	saves.insert("m_map", mapArr);
	QJsonDocument document;
	document.setObject(saves);
	QByteArray bytearr = document.toJson(QJsonDocument::Compact);
	QtConcurrent::run(saveToDisk, bytearr, savePath);
}

int Player::getMyId() {
	return m_id;
}

void Player::load() {
	if (m_path.length() > 1) {
		QString loadPath = m_path + "_user.info";
		QJsonDocument document = QJsonDocument::fromJson(loadFromDisk(loadPath));
		if (!document.isNull()) {
			QJsonObject obj = document.object();
			m_hard = obj.take("m_hard").toInt();
			m_power = obj.take("m_power").toInt();
			m_mood = obj.take("m_mood").toInt();
		}
		checkStaus();
		backBag.load(m_path);
	}
}

Player::~Player() {
	Player::save();
}





BackBag::BackBag() {

}

void BackBag::save(QString userPath) {
	QString savePath = userPath + "_bag.info";
	QJsonArray arr;
	for (BagThing t : m_bagThing) {
		QJsonObject saves;
		saves.insert("id", t.id);
		saves.insert("num", t.num);
		saves.insert("name", t.name);
		arr.append(saves);
	}
	QJsonDocument document;
	document.setArray(arr);
	QByteArray bytearr = document.toJson(QJsonDocument::Compact);
	QtConcurrent::run(saveToDisk, bytearr, savePath);
}

void BackBag::load(QString userPath) {
	QString loadPath = userPath + "_bag.info";
	savePath = userPath;
	QJsonDocument document = QJsonDocument::fromJson(loadFromDisk(loadPath));
	if (!document.isNull()) {
		QJsonArray jsonArr = document.array();
		for (int i = 0; i < 12; i++) {
			QJsonObject job = jsonArr.at(i).toObject();
			m_bagThing[i].id = job.take("id").toInt();
			m_bagThing[i].num = job.take("num").toInt();
			m_bagThing[i].name = job.take("name").toString();
		}
	}
}

void BackBag::newBag() {
	for (int i = 0; i < 12; i++) {
	m_bagThing[i].id = i;
	m_bagThing[i].num = 0;
	}
}

BagThing BackBag::getBagThing(int thing) {
	return m_bagThing[thing];
}

BagThing* BackBag::getBagThing() {
	return m_bagThing;
}

void BackBag::addBagThing(int thing) {
	m_bagThing[thing - 1].num++;
	BackBag::save(savePath);
}

void BackBag::useBagThing(int thing) {
	if (m_bagThing[thing - 1].num > 0) {
		m_bagThing[thing - 1].num--;
		BackBag::save(savePath);
	}
}

BackBag::~BackBag() {
	save(savePath);
}



