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

    keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    visibleSize = Director::getInstance()->getVisibleSize();
    MakeBackground();
    MakeUI();
    return true;
}

void MainScene::MakeBackground() {
    experimental::AudioEngine::play2d("sounds/MainTheme.mp3", true);
    auto backgroundImage = Sprite::create("images/BackgroundFridge.png");
    backgroundImage->setScale(visibleSize.width / backgroundImage->getContentSize().width, visibleSize.height / backgroundImage->getContentSize().height);
    backgroundImage->setAnchorPoint(Point::ZERO);
    this->addChild(backgroundImage, 0);
}

void MainScene::MakeUI() {
    bestScore = UserDefault::getInstance()->getIntegerForKey("bestScore", 0);
    waterdrop = UserDefault::getInstance()->getIntegerForKey("waterdrop", 0);
    HP = UserDefault::getInstance()->getIntegerForKey("HP", 10);
    fruitType = "Apple";
    UserDefault::getInstance()->setStringForKey("selectedFruit", fruitType);

    // 최고점수 레이블 생성
    auto bestScoreLabel = Label::create("최고점수:" + to_string(bestScore), "fonts/DungGeunMo.ttf", visibleSize.width / 16);
    bestScoreLabel->setColor(Color3B(0, 0, 0));
    bestScoreLabel->setPosition(visibleSize.width * 0.25, visibleSize.height * 0.8);

    this->addChild(bestScoreLabel, 1);

    // 소유하고 있는 물방울 표시
    auto waterdropSprite = Sprite::create("images/Waterdrop.png");
    waterdropSprite->setScale((visibleSize.width / waterdropSprite->getContentSize().width) / 20);
    waterdropSprite->setPosition(-visibleSize.width / 30, visibleSize.height / 16);

    waterdropText = ui::Text::create("x" + to_string(waterdrop), "fonts/DungGeunMo.ttf", visibleSize.width / 12);
    waterdropText->setColor(Color3B(0, 0, 0));
    waterdropText->setPosition(Point(visibleSize.width * 0.25, visibleSize.height * 0.5));
    waterdropText->addChild(waterdropSprite);

    this->addChild(waterdropText, 1);

    // 체력 표시
    auto HPLabel = Label::create("HP", "fonts/DungGeunMo.ttf", visibleSize.width / 16);
    HPLabel->setColor(Color3B(255, 0, 0));
    HPLabel->setPosition(Point(visibleSize.width / 18, visibleSize.width / 10));

    HPText = ui::Text::create(to_string(HP), "fonts/DungGeunMo.ttf", visibleSize.width / 16);
    HPText->setColor(Color3B(0, 0, 0));
    HPText->setPosition(Point(visibleSize.width * 0.1, visibleSize.height * 0.15));
    HPText->addChild(HPLabel);

    this->addChild(HPText, 1);

    // 필요한 물방울 갯수
    if (HP >= 100) {
        needWaterdropText = ui::Text::create("최대 체력", "fonts/DungGeunMo.ttf", visibleSize.width / 20);
    }
    else{
        needWaterdropText = ui::Text::create("필요한 물방울" + to_string(HP * 2) + "개", "fonts/DungGeunMo.ttf", visibleSize.width / 36);

        // 강화 버튼
        auto upgradeHPMenuItem = MenuItemFont::create("강화하기", CC_CALLBACK_0(MainScene::UpgradeHP, this));
        upgradeHPMenuItem->setColor(Color3B(255, 255, 255));
        upgradeHPMenuItem->setPosition(Point(visibleSize.width * 0.3, visibleSize.height * 0.15));
        upgradeHPMenuItem->setFontNameObj("fonts/DungGeunMo.ttf");
        upgradeHPMenuItem->setScale(visibleSize.width / 800);

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
    appleMenuItem->setScale((visibleSize.width / appleSprite->getContentSize().width) / 10);

    // 오렌지
    auto orangeSprite = Sprite::create("images/Orange.png");
    auto orangeMenuItem = MenuItemSprite::create(Sprite::createWithTexture(orangeSprite->getTexture(), Rect(0, 0, orangeSprite->getContentSize().width, orangeSprite->getContentSize().height / 2)),
                                                 Sprite::createWithTexture(orangeSprite->getTexture(), Rect(0, orangeSprite->getContentSize().height / 2, orangeSprite->getContentSize().width, orangeSprite->getContentSize().height / 2)));
    orangeMenuItem->setCallback(CC_CALLBACK_0(MainScene::SelectFruit, this, "orange"));
    orangeMenuItem->setScale((visibleSize.width / orangeSprite->getContentSize().width) / 10);

    // 배
    auto pearSprite = Sprite::create("images/Pear.png");
    auto pearMenuItem = MenuItemSprite::create(Sprite::createWithTexture(pearSprite->getTexture(), Rect(0, 0, pearSprite->getContentSize().width, pearSprite->getContentSize().height / 2)),
                                               Sprite::createWithTexture(pearSprite->getTexture(), Rect(0, pearSprite->getContentSize().height / 2, pearSprite->getContentSize().width, pearSprite->getContentSize().height / 2)));
    pearMenuItem->setCallback(CC_CALLBACK_0(MainScene::SelectFruit, this, "pear"));
    pearMenuItem->setScale((visibleSize.width / pearSprite->getContentSize().width) / 10);

    fruitMenu = Menu::create(appleMenuItem, orangeMenuItem, pearMenuItem, NULL);
    fruitMenu->setPosition(Point(visibleSize.width * 0.76, visibleSize.height * 0.76));
    fruitMenu->alignItemsHorizontally();

    this->addChild(fruitMenu, 1);

    selectedSprite = Sprite::create("images/Arrow.png");
    selectedSprite->setPosition(fruitMenu->getPositionX() - visibleSize.width / 9.5, fruitMenu->getPositionY() - visibleSize.width / 10);
    selectedSprite->setScale((visibleSize.width / selectedSprite->getContentSize().width) / 16);
    UserDefault::getInstance()->setStringForKey("selectedFruit", "Apple");

    auto action = MoveBy::create(0.5, Point(0, 20));
    auto seq = Sequence::create(action, action->reverse(), NULL);
    selectedSprite->runAction(RepeatForever::create(seq));

    this->addChild(selectedSprite , 1);

    // 게임 시작
    auto startMenuItem = MenuItemFont::create("게임시작", CC_CALLBACK_0(MainScene::Start, this));
    startMenuItem->setColor(Color3B(0, 0, 0));
    startMenuItem->setPosition(Point(visibleSize.width * 0.75, visibleSize.height * 0.25));
    startMenuItem->setFontNameObj("fonts/DungGeunMo.ttf");
    startMenuItem->setScale(visibleSize.width / 480);

    auto menu = Menu::create(startMenuItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu, 2);
}

void MainScene::SelectFruit(string type) {

    if (type == "apple") {
        fruitType = "Apple";
		selectedSprite->setPosition(fruitMenu->getPositionX() - visibleSize.width / 9.5, fruitMenu->getPositionY() - visibleSize.width / 10);
    }
    else if (type == "orange") {
        fruitType = "Orange";
		selectedSprite->setPosition(fruitMenu->getPositionX(), fruitMenu->getPositionY() - visibleSize.width / 10);
    }
    else if (type == "pear") {
        fruitType = "Pear";
		selectedSprite->setPosition(fruitMenu->getPositionX() + visibleSize.width / 9.5, fruitMenu->getPositionY() - visibleSize.width / 10);
    }
    UserDefault::getInstance()->setStringForKey("selectedFruit", fruitType);
}

void MainScene::UpgradeHP() {
    if (waterdrop >= HP * 2) {
        waterdrop -= HP * 2;
        waterdropText->setText(to_string(waterdrop));
        HP += 5;
        HPText->setText(to_string(HP));
        needWaterdropText->setText("필요한 물방울" + to_string(HP * 2) + "개");
        UserDefault::getInstance()->setIntegerForKey("HP", HP);
        UserDefault::getInstance()->setIntegerForKey("waterdrop", waterdrop);
    }
}

void MainScene::Start() {
    _eventDispatcher->removeEventListener(keyListener);
    experimental::AudioEngine::stopAll();
    UserDefault::getInstance()->flush();
    Director::getInstance()->replaceScene(GameScene::createScene());
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
        Director::getInstance()->end();
}