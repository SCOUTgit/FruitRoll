#include "Obstacle.h"

Obstacle::Obstacle(string name)
{
	obstacleImage = Sprite::create("images/" + name + ".png");
	Remove(name);
}


Obstacle::~Obstacle()
{
}

void Obstacle::Move() {
	auto action = MoveBy::create(1, ccp(-1000, 0));
	auto rf = RepeatForever::create(action);
	rf->setTag(0);
	obstacleImage->runAction(rf);
}

void Obstacle::Remove(string name) {
	if (name == "Coke" || name == "Bottle") {
		obstacleImage->setPosition(1700, 200 + obstacleImage->getContentSize().height / 2);
	}
	if (name == "Knife" || name == "Fork") {
		obstacleImage->setPosition(1700, 700);
	}
}

void Obstacle::Stop() {
	obstacleImage->stopActionByTag(0);
	stopping = true;
}

void Obstacle::StopEnd() {
	stopping = false;
	Move();
}

void Obstacle::Fall() {
	auto action = MoveBy::create(1, ccp(0, -300));
	obstacleImage->runAction(action);
}

bool Obstacle::CheckNeedDelete() {
	if (obstacleImage->getPosition().x < -obstacleImage->getContentSize().width / 2)
		return true;
	return false;
}