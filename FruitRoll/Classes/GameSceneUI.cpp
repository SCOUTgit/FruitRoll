#include "GameSceneUI.h"


GameSceneUI::GameSceneUI() {
	visibleSize = Director::getInstance()->getVisibleSize();
	MakeButton();
	MakeInfo();
}

GameSceneUI::~GameSceneUI() {

}

void GameSceneUI::MakeButton() {
	// 점프 버튼 만들기
	auto jumpButtonLabel = Label::create("Jump", "fonts/DungGeunMo.ttf", visibleSize.width / 8);
	jumpButtonLabel->setColor(Color3B(255, 255, 255));

	jumpButton = Sprite::create("images/Button.png");

	auto jumpButtonScale = (visibleSize.width / jumpButton->getContentSize().width) / 4;

	jumpButton->setScale(jumpButtonScale);
	jumpButton->addChild(jumpButtonLabel, 1);
	jumpButton->setPosition(jumpButton->getContentSize().width * jumpButtonScale * 0.5, jumpButton->getContentSize().height * jumpButtonScale * 0.5);
	jumpButtonLabel->setScale(0.5 / jumpButtonScale);
	jumpButtonLabel->setPosition(jumpButton->getContentSize().width * 0.5, jumpButton->getContentSize().height * 0.5);

	// 스탑 버튼 만들기
	auto stopButtonLabel = Label::create("Stop", "fonts/DungGeunMo.ttf", visibleSize.width / 8);
	stopButtonLabel->setColor(Color3B(255, 255, 255));

	stopButton = Sprite::create("images/Button.png");

	auto stopButtonScale = (visibleSize.width / stopButton->getContentSize().width) / 4;

	stopButton->setScale(stopButtonScale);
	stopButton->addChild(stopButtonLabel, 1);
	stopButton->setPosition(visibleSize.width - stopButton->getContentSize().width * stopButtonScale * 0.5, stopButton->getContentSize().height * stopButtonScale * 0.5);
	stopButtonLabel->setScale(0.5 / stopButtonScale);
	stopButtonLabel->setPosition(stopButton->getContentSize().width * 0.5, stopButton->getContentSize().height * 0.5);

	// 일시정지 버튼 만들기
	pauseButton = MenuItemImage::create("images/PauseButton.png", "images/PauseButton.png");

	auto pauseButtonScale = (visibleSize.width / pauseButton->getContentSize().width) / 15;

	pauseButton->setScale(pauseButtonScale);
	pauseButton->setPosition(visibleSize.width * 0.9, visibleSize.height * 0.9);
}

void GameSceneUI::MakeInfo() {
	healthLabel = Label::create("HP","fonts/DungGeunMo.ttf", visibleSize.width / 12);
	healthLabel->setColor(Color3B(0, 0, 0));
	healthLabel->setPosition(visibleSize.width * 0.1, visibleSize.height * 0.9);

	healthBar = ui::LoadingBar::create("images/HealthBar.png", 100);
	healthBar->setScale(visibleSize.width / 1280);
	healthBar->setPosition(Point(visibleSize.width * 0.3, visibleSize.height * 0.9));
	healthBar->setDirection(ui::LoadingBar::Direction::LEFT);

	healthBarBackground = Sprite::create("images/HealthBarBackground.png");
	healthBarBackground->setScale(visibleSize.width / 1280);
	healthBarBackground->setPosition(Point(visibleSize.width * 0.3, visibleSize.height * 0.9));
	healthBarBackground->setOpacity(200);

	auto scoreSprite = Sprite::create("images/Waterdrop.png");
	scoreSprite->setScale((visibleSize.width / scoreSprite->getContentSize().width) / 20);
	scoreSprite->setPosition(-visibleSize.width / 30, 50);

	scoreText = ui::Text::create("x0", "fonts/DungGeunMo.ttf", visibleSize.width / 14);
	scoreText->setColor(Color3B(0, 0, 0));
	scoreText->setPosition(Point(visibleSize.width * 0.6, visibleSize.height * 0.9));
	scoreText->addChild(scoreSprite);
}

void GameSceneUI::UpdateInfo(int hp, int score) {
	healthBar->setPercent(hp);
	scoreText->setText("x" + to_string(score));
}