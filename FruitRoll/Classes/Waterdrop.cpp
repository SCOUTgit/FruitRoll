#include "Waterdrop.h"


Waterdrop::Waterdrop()
{
	waterdropImage = Sprite::create("images/Waterdrop.png");
	waterdropImage->setPosition(1700, 300);
	waterdropImage->setScale(0.4);
	Move();
}

Waterdrop::~Waterdrop()
{
}

bool Waterdrop::CollideCheck(float x, float y, float size) {
	float waterdropX = waterdropImage->getPositionX();
	float waterdropY = waterdropImage->getPositionY();
	if (waterdropX <= x + size && waterdropX >= x && waterdropY <= y + size && waterdropY >= y)
		return true;

	return false;
}

void Waterdrop::Move() {
	auto action = MoveBy::create(1, ccp(-1000, 0));
	auto rf = RepeatForever::create(action);
	rf->setTag(0);
	waterdropImage->runAction(rf);
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
	if (waterdropImage->getPosition().x < -waterdropImage->getContentSize().width / 2)
		return true;
	return false;
}