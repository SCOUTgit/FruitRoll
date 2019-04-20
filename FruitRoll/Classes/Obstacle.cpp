#include "Obstacle.h"

Obstacle::Obstacle(string type)
{
	string name;
	if (type == "Fixed") {
		srand(time(NULL));
		int random = rand() % 2;
		switch (random) {
		case 0:
			name = "Bottle";
			break;
		case 1:
			name = "Coke";
			break;
		}
		obstacleImage = Sprite::create("images/" + name + ".png");
		obstacleImage->setPosition(1700, 350);
	}
	else if (type == "Falling") {
		srand(time(NULL));
		int random = rand() % 2;
		switch (random) {
		case 0:
			name = "Knife";
			break;
		case 1:
			name = "Fork";
			break;
		}
		obstacleImage = Sprite::create("images/" + name + ".png");
		obstacleImage->setPosition(1700, 700);
	}

	obstacleImage->setScale(0.7);
	Move();
	if (type == "Falling")
		Fall();
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