#include "MainScene.h"

Scene* MainScene::createScene() {
	auto scene = Scene::create();
	auto layer = MainScene::create();
	
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	MakeBackground();
	MakeUI();
	return true;
}

void MainScene::MakeBackground() {
	auto backgroundImage = Sprite::create("images/BackgroundFridge.png");
	backgroundImage->setScale(visibleSize.width / backgroundImage->getContentSize().width, visibleSize.height / backgroundImage->getContentSize().height);
	backgroundImage->setAnchorPoint(Point::ZERO);
	this->addChild(backgroundImage, 0);
	
}

void MainScene::MakeUI() {
	bestScore = 10000;
	waterdrop = 23;
	HP = 30;

	// 최고점수 레이블 생성
	auto bestScoreLabel = Label::create("최고점수:" + to_string(bestScore), "fonts/DungGeunMo.ttf", 70);
	bestScoreLabel->setColor(Color3B(0, 0, 0));
	bestScoreLabel->setPosition(visibleSize.width * 0.25, visibleSize.height * 0.8);

	this->addChild(bestScoreLabel, 1);

	// 소유하고 있는 물방울 표시
	auto waterdropSprite = Sprite::create("images/Waterdrop.png");
	waterdropSprite->setScale((visibleSize.width / waterdropSprite->getContentSize().width) / 20);
	waterdropSprite->setPosition(-visibleSize.width / 30, 50);

	auto watedropText = ui::Text::create("x" + to_string(waterdrop), "fonts/DungGeunMo.ttf", 100);
	watedropText->setColor(Color3B(0, 0, 0));
	watedropText->setPosition(Point(visibleSize.width * 0.25, visibleSize.height * 0.5));
	watedropText->addChild(waterdropSprite);

	this->addChild(watedropText, 1);

	// 체력 표시
	auto HPLabel = Label::create("HP", "fonts/DungGeunMo.ttf", 100);
	HPLabel->setColor(Color3B(255, 0, 0));
	HPLabel->setPosition(Point(75, 150));

	HPText = ui::Text::create(to_string(HP), "fonts/DungGeunMo.ttf", 100);
	HPText->setColor(Color3B(0, 0, 0));
	HPText->setPosition(Point(visibleSize.width * 0.1, visibleSize.height * 0.15));
	HPText->addChild(HPLabel);

	this->addChild(HPText, 1);

	// 필요한 물방울 갯수
	if (HP >= 100) {
		needWaterdropText = ui::Text::create("최대 체력", "fonts/DungGeunMo.ttf", 50);
	}
	else{
		needWaterdropText = ui::Text::create("필요한 물방울" + to_string(HP * 5) + "개", "fonts/DungGeunMo.ttf", 35);
		
		// 강화 버튼
		auto upgradeHPMenuItem = MenuItemFont::create("강화하기", CC_CALLBACK_0(MainScene::UpgradeHP, this));
		upgradeHPMenuItem->setColor(Color3B(0, 0, 0));
		upgradeHPMenuItem->setPosition(Point(visibleSize.width * 0.3, visibleSize.height * 0.15));
		upgradeHPMenuItem->setFontNameObj("fonts/DungGeunMo.ttf");
		upgradeHPMenuItem->setScale(1.5);

		auto upgradeButtonSprite = Sprite::create("images/Button.png");
		upgradeButtonSprite->setScale(upgradeHPMenuItem->getContentSize().width / upgradeButtonSprite->getContentSize().width);
		upgradeButtonSprite->setPosition(Point(visibleSize.width * 0.3, visibleSize.height * 0.15));
		upgradeButtonSprite->setScale(upgradeHPMenuItem->getBoundingBox().getMinX() / upgradeButtonSprite->getContentSize().width, 
			upgradeHPMenuItem->getBoundingBox().getMinY() / upgradeButtonSprite->getContentSize().height);

		auto menu = Menu::create(upgradeHPMenuItem, NULL);
		menu->setPosition(Point::ZERO);

		this->addChild(menu, 2);
		this->addChild(upgradeButtonSprite, 1);
	}
	needWaterdropText->setColor(Color3B(0, 0, 0));
	needWaterdropText->setPosition(Point(visibleSize.width * 0.3, visibleSize.height * 0.25));

	this->addChild(needWaterdropText, 1);
	
	// 과일들 스프라이트
	// 사과
	auto appleSprite = Sprite::create("images/Apple.png");
	auto appleMenuItem = MenuItemSprite::create(Sprite::createWithTexture(appleSprite->getTexture(), Rect(0, 0, appleSprite->getContentSize().width, appleSprite->getContentSize().height / 2)),
		Sprite::createWithTexture(appleSprite->getTexture(), Rect(0, appleSprite->getContentSize().height / 2, appleSprite->getContentSize().width, appleSprite->getContentSize().height / 2)));
	appleMenuItem->setCallback(CC_CALLBACK_0(MainScene::SelectFruit,this,"apple"));
	appleMenuItem->setScale(0.25);

	// 오렌지
	auto orangeSprite = Sprite::create("images/Orange.png");
	auto orangeMenuItem = MenuItemSprite::create(Sprite::createWithTexture(orangeSprite->getTexture(), Rect(0, 0, orangeSprite->getContentSize().width, orangeSprite->getContentSize().height / 2)),
		Sprite::createWithTexture(orangeSprite->getTexture(), Rect(0, orangeSprite->getContentSize().height / 2, orangeSprite->getContentSize().width, orangeSprite->getContentSize().height / 2)));
	orangeMenuItem->setCallback(CC_CALLBACK_0(MainScene::SelectFruit, this, "orange"));
	orangeMenuItem->setScale(0.25);

	// 배
	auto pearSprite = Sprite::create("images/Pear.png");
	auto pearMenuItem = MenuItemSprite::create(Sprite::createWithTexture(pearSprite->getTexture(), Rect(0, 0, pearSprite->getContentSize().width, pearSprite->getContentSize().height / 2)),
		Sprite::createWithTexture(pearSprite->getTexture(), Rect(0, pearSprite->getContentSize().height / 2, pearSprite->getContentSize().width, pearSprite->getContentSize().height / 2)));
	pearMenuItem->setCallback(CC_CALLBACK_0(MainScene::SelectFruit, this, "paer"));
	pearMenuItem->setScale(0.25);

	fruitMenu = Menu::create(appleMenuItem, orangeMenuItem, pearMenuItem, NULL);
	fruitMenu->setPosition(Point(visibleSize.width * 0.76, visibleSize.height * 0.76));
	fruitMenu->alignItemsHorizontally();

	this->addChild(fruitMenu, 1);

	selectedSprite = Sprite::create("images/Arrow.png");
	selectedSprite->setPosition(fruitMenu->getPositionX() - 160, fruitMenu->getPositionY() - 150);
	selectedSprite->setScale(0.5);

	auto action = MoveBy::create(0.5, Point(0, 20));
	auto seq = Sequence::create(action, action->reverse(), NULL);
	selectedSprite->runAction(RepeatForever::create(seq));

	this->addChild(selectedSprite , 1);

	// 게임 시작
	auto startMenuItem = MenuItemFont::create("게임시작", CC_CALLBACK_0(MainScene::Start, this));
	startMenuItem->setColor(Color3B(0, 0, 0));
	startMenuItem->setPosition(Point(visibleSize.width * 0.75, visibleSize.height * 0.25));
	startMenuItem->setFontNameObj("fonts/DungGeunMo.ttf");
	startMenuItem->setScale(3);

	auto menu = Menu::create(startMenuItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu, 2);	
}

void MainScene::SelectFruit(string type) {

}

void MainScene::UpgradeHP() {

}

void MainScene::Start() {

}