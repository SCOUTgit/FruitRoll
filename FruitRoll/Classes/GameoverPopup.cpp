#include "GameoverPopup.h"

GameoverPopup * GameoverPopup::create() {
	GameoverPopup *ret = new GameoverPopup();
	if (ret && ret->init())
	{
		ret->autorelease();
	}

	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GameoverPopup::init() {

	MakePopUp();

	return true;
}

void GameoverPopup::onEnter() {
	Layer::onEnter();

	setTouchEnabled(true);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameoverPopup::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameoverPopup::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameoverPopup::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameoverPopup::onTouchBegan(Touch* touch, Event* unused_event) {
	auto touchPoint = touch->getLocation();
	
	if (restartButton->getBoundingBox().containsPoint(touchPoint)) {
		clickedButton = "restart";
		restartButton->setOpacity(128);
	}
	else if (goMainButton->getBoundingBox().containsPoint(touchPoint)) {
		clickedButton = "goMain";
		goMainButton->setOpacity(128);
	}
	else
		clickedButton = "";
	return true;
}

void GameoverPopup::onTouchMoved(Touch* touch, Event* unused_event) {
	auto touchPoint = touch->getLocation();
	
	if (restartButton->getBoundingBox().containsPoint(touchPoint)) {
		clickedButton = "restart";
		restartButton->setOpacity(128);
		goMainButton->setOpacity(255);
	}
	else if (goMainButton->getBoundingBox().containsPoint(touchPoint)) {
		clickedButton = "goMain";
		restartButton->setOpacity(255);
		goMainButton->setOpacity(128);
	}
	else
		clickedButton = "";
}

void GameoverPopup::onTouchEnded(Touch* touch, Event *unused_event) {
	restartButton->setOpacity(255);
	goMainButton->setOpacity(255);
	auto touchPoint = touch->getLocation();
	
	if (restartButton->getBoundingBox().containsPoint(touchPoint) && clickedButton == "restart") {
		OnClickRestart();
	}
	else if (goMainButton->getBoundingBox().containsPoint(touchPoint) && clickedButton == "goMain") {
		OnClickGoMain();
	}
}

void GameoverPopup::MakePopUp() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), visibleSize.width, visibleSize.height);

	this->addChild(fadeBack);

	fadeBack->runAction(FadeTo::create(0.5f, 200));

	auto pauseBG = Sprite::create("images/PopUp.png");

	pauseBG->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	pauseBG->setScale((visibleSize.width / pauseBG->getContentSize().width) / 2);
	this->addChild(pauseBG);

	auto restartButtonLabel = Label::create("다시시작", "fonts/DungGeunMo.ttf", visibleSize.width / 10);
	restartButtonLabel->setColor(Color3B(255, 255, 255));

	restartButton = Sprite::create("images/Button.png");
	auto buttonScale = (visibleSize.width / restartButton->getContentSize().width) / 4;

	restartButton->setScale(buttonScale);
	restartButton->addChild(restartButtonLabel, 1);
	restartButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	restartButtonLabel->setScale(0.5 / buttonScale);
	restartButtonLabel->setPosition(restartButton->getContentSize().width * 0.5, restartButton->getContentSize().height * 0.5);

	this->addChild(restartButton, 1);

	auto goMainButtonLabel = Label::create("메인화면", "fonts/DungGeunMo.ttf", visibleSize.width / 10);
	goMainButtonLabel->setColor(Color3B(255, 255, 255));

	goMainButton = Sprite::create("images/Button.png");

	goMainButton->setScale(buttonScale);
	goMainButton->addChild(goMainButtonLabel, 1);
	goMainButton->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2) - visibleSize.height / 4));
	goMainButtonLabel->setScale(0.5 / buttonScale);
	goMainButtonLabel->setPosition(goMainButton->getContentSize().width * 0.5, goMainButton->getContentSize().height * 0.5);

	this->addChild(goMainButton, 1);

	// 획득한 물방울 출력
	auto scoreSprite = Sprite::create("images/Waterdrop.png");
	scoreSprite->setScale((visibleSize.width / scoreSprite->getContentSize().width) / 20);
	scoreSprite->setPosition(Point(visibleSize.width * 0.4, visibleSize.height * 0.75));

	scoreText = ui::Text::create("", "fonts/DungGeunMo.ttf", visibleSize.width/20);
	scoreText->setColor(Color3B(0, 0, 0));
	scoreText->setPosition(Point(visibleSize.width * 0.55, visibleSize.height * 0.75));
	this->addChild(scoreText, 1);
	this->addChild(scoreSprite, 1);
}

void GameoverPopup::OnClickRestart() {
	((GameScene *)this->getParent())->Restart();
	this->removeFromParentAndCleanup(true);
}

void GameoverPopup::OnClickGoMain() {
	((GameScene *)this->getParent())->GoMain();
}

void GameoverPopup::GetInfo(int score) {
	scoreText->setText(to_string(score) + "개 획득");
}