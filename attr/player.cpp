#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

}

Player* Player::Instance = new Player();

Player* Player::getInstance() {
	return Instance;
}
