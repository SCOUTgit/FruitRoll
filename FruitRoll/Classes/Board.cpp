#include "Board.h"


Board::Board()
{
	stopping = false;
	boardImage = Sprite::create("images/Board.png");
	visibleSize = Director::getInstance()->getVisibleSize();
	auto scale = visibleSize.width / 3200;
	boardImage->setScale(scale);
	width = boardImage->getContentSize().width * scale;
	height = boardImage->getContentSize().height * scale;
	Remove();
	Move();
}

Board::~Board()
{
}

void Board::Move() {
	auto action = MoveBy::create(1, ccp(-visibleSize.width / 1.6, 0));
	auto rf = RepeatForever::create(action);
	rf->setTag(0);
	boardImage->runAction(rf);
}

void Board::Remove() {
	boardImage->setPosition(width * 1.5, height * 1.5);
}

void Board::Stop() {
	boardImage->stopActionByTag(0);
	stopping = true;
}

void Board::StopEnd() {
	stopping = false;
	Move();
}

bool Board::CheckNeedDelete() {
	if (boardImage->getPosition().x < -width / 2)
		return true;
	return false;
}