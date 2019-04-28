#include "GameSceneUI.h"


GameSceneUI::GameSceneUI() {
	visibleSize = Director::getInstance()->getVisibleSize();
	MakeButton();
}

GameSceneUI::~GameSceneUI() {

}

void GameSceneUI::MakeButton() {
	// 점프 버튼 만들기
	auto jumpButtonLabel = Label::create("Jump", "fonts/DungGeunMo.ttf", 200);
	jumpButtonLabel->setColor(Color3B(255, 255, 255));

	jumpButton = Sprite::create("images/Button1.png");

	auto jumpButtonScale = (visibleSize.width / jumpButton->getContentSize().width) / 6;

	jumpButton->setScale(jumpButtonScale);
	jumpButton->setPosition(jumpButton->getContentSize().width * jumpButtonScale * 0.75, jumpButton->getContentSize().height * jumpButtonScale);
	jumpButton->addChild(jumpButtonLabel, 1);
	jumpButtonLabel->setPosition(jumpButtonLabel->getContentSize().width, jumpButtonLabel->getContentSize().height);

	// 스탑 버튼 만들기
	auto StopButtonLabel = Label::create("Stop", "fonts/DungGeunMo.ttf", 200);
	StopButtonLabel->setColor(Color3B(255, 255, 255));

	stopButton = Sprite::create("images/Button1.png");

	auto StopButtonScale = (visibleSize.width / stopButton->getContentSize().width) / 6;

	stopButton->setScale(StopButtonScale);
	stopButton->setPosition(visibleSize.width - stopButton->getContentSize().width * StopButtonScale * 0.75, stopButton->getContentSize().height * StopButtonScale);
	stopButton->addChild(StopButtonLabel, 1);
	StopButtonLabel->setPosition(StopButtonLabel->getContentSize().width, StopButtonLabel->getContentSize().height);

	// 일시정지 버튼 만들기
	pauseButton = MenuItemImage::create("images/PauseButton.png", "images/PauseButton.png");

	auto pauseButtonScale = (visibleSize.width / pauseButton->getContentSize().width) / 10;
	
	pauseButton->setScale(pauseButtonScale);
	pauseButton->setPosition(visibleSize.width * 0.9, visibleSize.height * 0.9);
}

void GameSceneUI::MakeInfo() {
	healthLabel = Label::create("HP : ","fonts/DungGeunMo.ttf", 200);
	healthBar = LoadingBar::create("images/HealthBar.png", 100);
	healthBar->setDirection(LoadingBar::Direction::RIGHT);

}

void GameSceneUI::UpdateInfo() {

}