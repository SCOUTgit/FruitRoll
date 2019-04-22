#include "Fruit.h"


Fruit::Fruit(string type)
{
	fruitType = type;
	MakeSprite();
	jumping = false;
	stopping = false;
}

Fruit::~Fruit()
{
	fruitAnimation->release();
}

void Fruit::MakeSprite() {
	auto fruitSprite = Sprite::create("images/" + fruitType + ".png");
	auto sizeX = fruitSprite->getContentSize().width;
	auto sizeY = fruitSprite->getContentSize().height / 2;

	fruitAnimation = Animation::create();

	fruitAnimation->setDelayPerUnit(0.3);

	fruitAnimation->addSpriteFrameWithTexture(fruitSprite->getTexture(), Rect(0, sizeX, sizeX, sizeY));
	fruitAnimation->addSpriteFrameWithTexture(fruitSprite->getTexture(), Rect(0, 0, sizeX, sizeY));
	fruitAnimation->addSpriteFrameWithTexture(fruitSprite->getTexture(), Rect(0, sizeX, sizeX, sizeY));
	fruitAnimation->addSpriteFrameWithTexture(fruitSprite->getTexture(), Rect(0, 0, sizeX, sizeY));

	fruitAnimation->retain();

	fruitImage = Sprite::createWithTexture(fruitSprite->getTexture(), Rect(0, 0, sizeX, sizeY));
	fruitImage->setPosition(200, 300);
	fruitImage->setScale(0.4);
}

void Fruit::Jump() {
	jumping = true;
	auto jumpAction = JumpTo::create(1, fruitImage->getPosition(), 400, 1);
	auto callback = CallFunc::create(CC_CALLBACK_0(Fruit::JumpEnd, this));
	auto seq = Sequence::create(jumpAction, callback, NULL);
	fruitImage->runAction(seq);
	Stop();
}

void Fruit::JumpEnd() {
	jumping = false;
	StopEnd();
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

void Fruit::PlayAnimation() {
	auto fruitAnimate = Animate::create(fruitAnimation);
	fruitImage->runAction(fruitAnimate);
}