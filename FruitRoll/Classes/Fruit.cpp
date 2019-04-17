#include "Fruit.h"


Fruit::Fruit(string type)
{
	fruitType = type;
	Health = 100;
	MakeAnimate();
}

Fruit::~Fruit()
{
}

void Fruit::MakeAnimate() {
	auto sprite = Sprite::create("images/" + fruitType + ".png");
	auto animation = Animation::create();
	
	auto sizeX = sprite->getContentSize().width;
	auto sizeY = sprite->getContentSize().height / 2;

	animation->setDelayPerUnit(0.3);
	
	animation->addSpriteFrameWithTexture(sprite->getTexture(), Rect(0, 0, sizeX, sizeY));
	animation->addSpriteFrameWithTexture(sprite->getTexture(), Rect(0, sizeX, sizeX, sizeY));
	
	fruitImage = Sprite::createWithTexture(sprite->getTexture(), Rect(0, 0, sizeX, sizeY));
	fruitImage->setPosition(200, 300);
	fruitImage->setScale(0.4);

	fruitAnimate = Animate::create(animation);
}

void Fruit::Jump() {
	jumping = true;
	auto jumpAction = JumpTo::create(1, fruitImage->getPosition(), 400, 1);
	auto callback = CallFunc::create(CC_CALLBACK_0(Fruit::JumpEnd, this));
	auto seq = Sequence::create(jumpAction, callback, NULL);
	fruitImage->runAction(seq);
}

void Fruit::JumpEnd() {
	jumping = false;
}

void Fruit::Stop() {    
	stopping = true;
	fruitImage->stopActionByTag(0);
}

void Fruit::StopEnd() {
	stopping = false;    
	Rotate();
}

void Fruit::Rotate() {
	auto rotateAction = RotateBy::create(1, 540);
	auto repeatRotate = RepeatForever::create(rotateAction);
	repeatRotate->setTag(0);
	fruitImage->runAction(repeatRotate);
}

void Fruit::Collide() {
	Health -= 10;
	fruitImage->runAction(fruitAnimate);
}