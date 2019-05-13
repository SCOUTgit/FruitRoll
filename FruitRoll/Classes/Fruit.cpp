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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	fruitImage = Sprite::createWithTexture(fruitSprite->getTexture(), Rect(0, 0, sizeX, sizeY));
	fruitImage->setPosition(visibleSize.width / 8, visibleSize.height / 3);

	fruitImage->setScale((visibleSize.width / fruitImage->getContentSize().width) / 10);
	width = fruitImage->getContentSize().width * ((visibleSize.width / fruitImage->getContentSize().width) / 10);
	height = fruitImage->getContentSize().height * ((visibleSize.width / fruitImage->getContentSize().width) / 10);
	
	fruitRadius = width / 2;

	stopLable = Label::create("Stop!!", "fonts/DungGeunMo.ttf", visibleSize.width / 12);
	stopLable->setColor(Color3B(255, 50, 50));
	stopLable->setVisible(false);
	stopLable->setPosition(fruitImage->getPositionX(), fruitImage->getPositionY() + height);
	auto fadeIn = FadeTo::create(0.25, 155);
	auto fadeOut = FadeTo::create(0.25, 255);
	auto rf = RepeatForever::create(Sequence::create(fadeIn, fadeOut, NULL));
	stopLable->runAction(rf);
}

void Fruit::Jump() {
	jumping = true;
	auto jumpAction = JumpTo::create(1, fruitImage->getPosition(), height * 3, 1);
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
	auto fadeIn = FadeTo::create(0.25, 155);
	auto fadeOut = FadeTo::create(0.25, 255);
	fruitImage->runAction(fruitAnimate);
	auto seq = Sequence::create(fadeIn, fadeOut, fadeIn, fadeOut, NULL);
	fruitImage->runAction(seq);
}