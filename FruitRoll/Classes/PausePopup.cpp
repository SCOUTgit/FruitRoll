#include "PausePopup.h"

PausePopup * PausePopup::create() {
    PausePopup *ret = new PausePopup();
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

bool PausePopup::init() {

    MakePopUp();

    return true;
}

void PausePopup::onEnter() {
    Layer::onEnter();

    setTouchEnabled(true);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PausePopup::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PausePopup::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PausePopup::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool PausePopup::onTouchBegan(Touch* touch, Event* unused_event) {
	auto touchPoint = touch->getLocation();
	if (resumeButton->getBoundingBox().containsPoint(touchPoint)) {
		clickedButton = "resume";
		resumeButton->setOpacity(128);
	}
	else if (restartButton->getBoundingBox().containsPoint(touchPoint)) {
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

void PausePopup::onTouchMoved(Touch* touch, Event* unused_event) {
	auto touchPoint = touch->getLocation();
	if (resumeButton->getBoundingBox().containsPoint(touchPoint)) {
		clickedButton = "resume";
		resumeButton->setOpacity(128);
		restartButton->setOpacity(255);
		goMainButton->setOpacity(255);

	}
	else if (restartButton->getBoundingBox().containsPoint(touchPoint)) {
		clickedButton = "restart";
		resumeButton->setOpacity(255);
		restartButton->setOpacity(128);
		goMainButton->setOpacity(255);
	}
	else if (goMainButton->getBoundingBox().containsPoint(touchPoint)) {
		clickedButton = "goMain";
		resumeButton->setOpacity(255);
		restartButton->setOpacity(255);
		goMainButton->setOpacity(128);
	}
	else
		clickedButton = "";
}

void PausePopup::onTouchEnded(Touch* touch, Event *unused_event) {
	resumeButton->setOpacity(255);
	restartButton->setOpacity(255);
	goMainButton->setOpacity(255);
	auto touchPoint = touch->getLocation();
	if (resumeButton->getBoundingBox().containsPoint(touchPoint) && clickedButton == "resume") {
		OnClickResume();
	}
	else if (restartButton->getBoundingBox().containsPoint(touchPoint) && clickedButton == "restart") {
		OnClickRestart();
	}
	else if (goMainButton->getBoundingBox().containsPoint(touchPoint) && clickedButton == "goMain") {
		OnClickGoMain();
	}
}

void PausePopup::MakePopUp() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), visibleSize.width, visibleSize.height);

    this->addChild(fadeBack);

    fadeBack->runAction(FadeTo::create(0.5f, 200));

	auto pauseBG = Sprite::create("images/PopUp.png");

	pauseBG->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	pauseBG->setScale((visibleSize.width / pauseBG->getContentSize().width) / 2);
	this->addChild(pauseBG);


	auto resumeButtonLabel = Label::create("돌아가기", "fonts/DungGeunMo.ttf", visibleSize.width / 10);
	resumeButtonLabel->setColor(Color3B(255, 255, 255));

	resumeButton = Sprite::create("images/Button.png");
	
	auto buttonScale = (visibleSize.width / resumeButton->getContentSize().width) / 4;

	resumeButton->setScale(buttonScale);
	resumeButton->addChild(resumeButtonLabel, 1);
	resumeButton->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2) + visibleSize.height / 4));
	resumeButtonLabel->setScale(0.5 / buttonScale);
	resumeButtonLabel->setPosition(resumeButton->getContentSize().width * 0.5, resumeButton->getContentSize().height * 0.5);
	
	this->addChild(resumeButton,1);

	auto restartButtonLabel = Label::create("다시시작", "fonts/DungGeunMo.ttf", visibleSize.width / 10);
	restartButtonLabel->setColor(Color3B(255, 255, 255));

	restartButton = Sprite::create("images/Button.png");

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
}

void PausePopup::OnClickResume() {
    ((GameScene *)this->getParent())->Resume();
    this->removeFromParentAndCleanup(true);
}

void PausePopup::OnClickRestart() {
    ((GameScene *)this->getParent())->Restart();
    this->removeFromParentAndCleanup(true);
}

void PausePopup::OnClickGoMain() {
    ((GameScene *)this->getParent())->GoMain();
}