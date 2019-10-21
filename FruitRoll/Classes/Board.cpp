#include "Board.h"


Board::Board(float moveTime)
{
	this->moveTime = moveTime;
	stopping = false;
	boardImage = Sprite::create("images/Board.png");
	visibleSize = Director::getInstance()->getVisibleSize();
	auto scale = visibleSize.width / 2000;
	boardImage->setScale(scale);
	width = boardImage->getContentSize().width * scale;
	height = boardImage->getContentSize().height * scale;
	Remove();
	Move();
	boardImage->setScaleX(scale * 1.1);
}

Board::~Board()
{
}

void Board::Move() {
	auto action = MoveBy::create(moveTime, Point(-visibleSize.width / 1.6, 0));
	auto rf = RepeatForever::create(action);
	rf->setTag(0);
	boardImage->runAction(rf);
}

void Board::Remove() {
	boardImage->setPosition(width * 1.5, height);
}

void Board::Stop() {
	boardImage->stopActionByTag(0);
	stopping = true;
}

void Board::StopEnd(float moveTime) {
	stopping = false;
	this->moveTime = moveTime;
	Move();
}

bool Board::CheckNeedDelete() {
	if (boardImage->getPosition().x < -width / 2)
		return true;
	return false;
}