#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

}

Player* Player::Instance = new Player();

void Player::checkStaus() {

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

void Player::addSatiety(int num) {
	Player::m_satiety += num;
	checkStaus();
}

void Player::minusSatiety(int num) {
	Player::m_satiety -= num;
	checkStaus();
}

Player* Player::getInstance() {
	return Player::Instance;
}



BackBag::BackBag() {

}

void BackBag::save() {

}

void BackBag::load() {

}

BagThing BackBag::getBagThing(int thing) {
	return m_bagThing[thing];
}

BagThing* BackBag::getBagThing() {
	return m_bagThing;
}

void BackBag::addBagThing(int thing) {
	m_bagThing[thing].num++;
}

BackBag::~BackBag() {
}



