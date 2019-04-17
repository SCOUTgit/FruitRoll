#include "Waterdrop.h"


Waterdrop::Waterdrop()
{
	waterdropImage = Sprite::create("images/Waterdrop.png");
	waterdropImage->setPosition(1500, 300);
	waterdropImage->setScale(0.4);
	needDelete = false;
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
	if (waterdropImage->getPositionX() >= -100) {
		auto action = MoveBy::create(0.01, ccp(-20, 0));
		action->setTag(0);
		auto callback = CallFunc::create(CC_CALLBACK_0(Waterdrop::Move, this));
		auto seq = Sequence::create(action, callback, NULL);
		waterdropImage->runAction(seq);
	}
	// ¼Ò¸ê
	else {
		needDelete = true;
	}
}
void Waterdrop::Stop() {
	waterdropImage->stopActionByTag(0);
	stopping = true;
}
void Waterdrop::StopEnd() {
	stopping = false;
	Move();
}