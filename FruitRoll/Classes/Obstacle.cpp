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
		obstacleImage->setPosition(1500, 300);
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
		obstacleImage->setPosition(1500, 700);
	}

	needDelete = false;
	obstacleImage->setScale(0.7);
	Move();
	if (type == "Falling")
		Fall();
}


Obstacle::~Obstacle()
{
}

bool Obstacle::CollideCheck(float x, float y, float size) {
	float obstacleX = obstacleImage->getPositionX();
	float obstacleY = obstacleImage->getPositionY();
	if (obstacleX <= x + size && obstacleX >= x && obstacleY <= y + size && obstacleY >= y)
		return true;

	return false;
}

void Obstacle::Move() {
	if (obstacleImage->getPositionX() >= -100) {
		auto action = MoveBy::create(0.01, ccp(-20, 0));
		action->setTag(0);
		auto callback = CallFunc::create(CC_CALLBACK_0(Obstacle::Move, this));
		auto seq = Sequence::create(action, callback, NULL);
		obstacleImage->runAction(seq);
	}
	// ¼Ò¸ê
	else {
		needDelete = true;
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
	auto action = MoveBy::create(1, ccp(0, -400));
	obstacleImage->runAction(action);
}