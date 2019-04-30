#include "Waterdrop.h"


Waterdrop::Waterdrop()
{
	waterdropImage = Sprite::create("images/Waterdrop.png");
	visibleSize = Director::getInstance()->getVisibleSize();
	auto scale = visibleSize.width / 6400;
	waterdropImage->setScale(scale);
	width = waterdropImage->getContentSize().width * scale;
	height = waterdropImage->getContentSize().height * scale;
	Remove();
}

Waterdrop::~Waterdrop()
{
}

void Waterdrop::Move() {
	auto action = MoveBy::create(1, Point(-visibleSize.width / 1.6, 0));
	auto rf = RepeatForever::create(action);
	rf->setTag(0);
	waterdropImage->runAction(rf);
	moving = true;
}

void Waterdrop::Remove() {
	srand(time(NULL));
	float n = (float)(rand() % 3) / 5;
	waterdropImage->setPosition(visibleSize.width + width, visibleSize.height * (0.3 + n));
	moving = false;
}

void Waterdrop::Stop() {
	waterdropImage->stopActionByTag(0);
	stopping = true;
}

void Waterdrop::StopEnd() {
	stopping = false;
	Move();
}

bool Waterdrop::CheckNeedDelete() {
	if (waterdropImage->getPosition().x < -width / 2)
		return true;
	return false;
}