#include "player.h"

extern void saveToDisk(QByteArray content, QString path);

extern QByteArray loadFromDisk(QString path);


Player::Player(QObject *parent) : QObject(parent) {

}

Player* Player::Instance = new Player();

void Player::checkStaus() {
	// if staus change, emit stausChange
}

void Player::addPower(int num) {
	Player::m_power += num;
	checkStaus();
}

void Player::minusPower(int num) {
	Player::m_power -= num;
	checkStaus();
}
void Player::addMood(int num) {
	Player::m_mood += num;
	checkStaus();
}

void Player::minusMood(int num) {
	Player::m_mood -= num;
	checkStaus();
}

BagThing *Player::getBagThing() {
	return backBag.getBagThing();
}

void Player::addBagThing(int num) {
	backBag.addBagThing(num);
}

int Player::nowStaus() {
	return m_staus;
}

void Player::save() {
	backBag.save();
}

void Player::load() {

}


Player* Player::getInstance() {
	return Player::Instance;
}

Player::~Player() {
	Player::save();
}





BackBag::BackBag() {
	for (int i = 0; i < 12; i++) {
		m_bagThing[i].id = i;
		m_bagThing[i].num = 2;
	}
}

void BackBag::save() {
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
	QtConcurrent::run(saveToDisk, bytearr, QString("userInfo/bag.info"));
}

void BackBag::load() {
	QJsonDocument document = QJsonDocument::fromJson(loadFromDisk(QString("userInfo/bag.info")));
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

BagThing BackBag::getBagThing(int thing) {
	return m_bagThing[thing];
}

BagThing* BackBag::getBagThing() {
	return m_bagThing;
}

void BackBag::addBagThing(int thing) {
	m_bagThing[thing].num++;
	BackBag::save();
}

BackBag::~BackBag() {
	save();
}



