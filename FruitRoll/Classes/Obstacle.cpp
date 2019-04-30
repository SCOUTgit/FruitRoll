#include "Obstacle.h"

Obstacle::Obstacle(string name)
{
	this->name = name;
	obstacleImage = Sprite::create("images/" + name + ".png");
	visibleSize = Director::getInstance()->getVisibleSize();
	auto scale = visibleSize.width / 2400;
	obstacleImage->setScale(scale);
	width = obstacleImage->getContentSize().width * scale;
	height = obstacleImage->getContentSize().height * scale;
	Remove();
	experimental::AudioEngine::preload("sounds/DropObstacle.mp3");
}


Obstacle::~Obstacle()
{
	experimental::AudioEngine::uncache("sounds/DropObstacle.mp3");
}

void Obstacle::Move() {
	moving = true;
	auto action = MoveBy::create(1, Point(-visibleSize.width / 1.6, 0));
	auto rf = RepeatForever::create(action);
	rf->setTag(0);
	obstacleImage->runAction(rf);
}

void Obstacle::Remove() {
	if (name == "Coke" || name == "Bottle") {
		obstacleImage->setPosition(visibleSize.width + width, visibleSize.height * 0.2 + height / 2);
	}
	if (name == "Knife" || name == "Fork") {
		obstacleImage->stopActionByTag(1);
		obstacleImage->setPosition(visibleSize.width + width, visibleSize.height * 0.8);
	}
	moving = false;
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
	auto action = MoveBy::create(0.25, Point(0, -visibleSize.height * 0.4));
	auto seq = Sequence::create(DelayTime::create(1.3), action, CallFunc::create(CC_CALLBACK_0(Obstacle::PlayEffect, this)), NULL);
	seq->setTag(1);
	obstacleImage->runAction(seq);
}

bool Obstacle::CheckNeedDelete() {
	if (obstacleImage->getPosition().x < -width / 2)
		return true;
	return false;
}

void Obstacle::PlayEffect() {
	int e = experimental::AudioEngine::play2d("sounds/DropObstacle.mp3");
}