#include "Board.h"


Board::Board()
{
	boardImage = Sprite::create("images/Board.png");
	boardImage->setPosition(boardImage->getContentSize().width * 1.5, 250);
	Move();
	madeBoard = false;
}

Board::~Board()
{
}

void Board::Move() {
	auto action = MoveBy::create(1, ccp(-1000, 0));
	auto rf = RepeatForever::create(action);
	rf->setTag(0);
	boardImage->runAction(rf);
}
void Board::Stop() {
	boardImage->stopActionByTag(0);
	stopping = true;
}
void Board::StopEnd() {
	stopping = false;
	Move();
}

bool Board::CheckNeedMake() {
	if (boardImage->getPosition().x <= boardImage->getContentSize().width / 2 + 28 && !madeBoard) {
		madeBoard = true;
		return true;
	}
	return false;
}

bool Board::CheckNeedDelete() {
	if (boardImage->getPosition().x < -boardImage->getContentSize().width / 2)
		return true;
	return false;
}