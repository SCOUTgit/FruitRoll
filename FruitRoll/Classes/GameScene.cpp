#include "GameScene.h"

Scene* GameScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene::create();

	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	health = UserDefault::getInstance()->getIntegerForKey("HP", 10);
	score = 0;
	fullHP = health;
	end = false;

	MakeFruit();
	MakeBackground();
	MakeObject();
	MakeUI();
	MoveObject();

	experimental::AudioEngine::play2d("sounds/BGM.mp3", true, 0.5);
	experimental::AudioEngine::preload("sounds/Waterdrop.mp3");

	this->schedule(schedule_selector(GameScene::Tick));

	return true;
}

void GameScene::Tick(float f) {
	DeleteObject();
	CheckCollide();
}

void GameScene::OnClickPause() {
	if (!end) {
		experimental::AudioEngine::pauseAll();

		fruit->fruitImage->pause();
		board1->boardImage->pause();
		board2->boardImage->pause();
		waterdrop->waterdropImage->pause();
		for (pair<string, Obstacle*> o : obstacleMap) {
			if (o.second->moving)
				o.second->obstacleImage->pause();
		}
		paused = true;
		this->addChild(PausePopup::create(), 110);
	}
}

void GameScene::onEnter() {
	Layer::onEnter();
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void GameScene::onExit() {
	Layer::onExit();
	_eventDispatcher->removeEventListener(listener);
	_eventDispatcher->removeEventListener(keyListener);
	experimental::AudioEngine::uncache("sounds/Waterdrop.mp3");
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event) {
	auto touchPoint = touch->getLocation();
	if (UI->jumpButton->getBoundingBox().containsPoint(touchPoint) && !fruit->jumping) {
		fruit->Jump();
		UI->jumpButton->setOpacity(128);
	}

	else if (UI->stopButton->getBoundingBox().containsPoint(touchPoint) && !fruit->jumping) {
		health--;
		UI->UpdateInfo((health * 100) / fullHP, score);
		fruit->stopLable->setVisible(true);
		fruit->Stop();
		board1->Stop();
		board2->Stop();
		waterdrop->Stop();
		for (pair<string, Obstacle*> o : obstacleMap) {
			o.second->Stop();
		}
		UI->stopButton->setOpacity(128);
		if (health <= 0 && !end) {
			end = true;
			GameOver();
		}
	}

	return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* unused_event) {
	auto touchPoint = touch->getLocation();
	
	if (UI->stopButton->getBoundingBox().containsPoint(touchPoint) && !fruit->jumping && !board1->stopping) {
		health--;
		UI->UpdateInfo((health * 100) / fullHP, score);
		fruit->stopLable->setVisible(true);
		fruit->Stop();
		board1->Stop();
		board2->Stop();
		waterdrop->Stop();
		
		for (pair<string, Obstacle*> o : obstacleMap) {
			o.second->Stop();
		}
		
		UI->stopButton->setOpacity(128);
		if (health <= 0 && !end) {
			end = true;
			GameOver();
		}
	}
	
	if (!UI->stopButton->getBoundingBox().containsPoint(touchPoint) && board1->stopping && !end) {
		fruit->stopLable->setVisible(false);
		
        if(!fruit->jumping)
            fruit->StopEnd();
		board1->StopEnd();
		board2->StopEnd();
		
		if (waterdrop->moving)
			waterdrop->StopEnd();
		
		for (pair<string, Obstacle*> o : obstacleMap) {
			if (o.second->moving)
				o.second->StopEnd();
		}
		UI->stopButton->setOpacity(255);
	}
}

void GameScene::onTouchEnded(Touch* touch, Event *unused_event) {
	auto touchPoint = touch->getLocation();
	
	if (board1->stopping && !end) {
		fruit->stopLable->setVisible(false);
		
		if(!fruit->jumping)
			fruit->StopEnd();
		
		board1->StopEnd();
		board2->StopEnd();
		
		if (waterdrop->moving)
			waterdrop->StopEnd();
		for (pair<string, Obstacle*> o : obstacleMap) {
			if (o.second->moving)
				o.second->StopEnd();
		}
	}
	
	UI->jumpButton->setOpacity(255);
	UI->stopButton->setOpacity(255);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK && !paused)
		OnClickPause();
}

// 배경 추가
void GameScene::MakeBackground() {
	// sceneType 정하기
	string type;
	srand(time(NULL));
	int n = rand() % 2;
	switch (n) {
		case 0:
			type = "FridgeStage";
			break;
		case 1:
			type = "KitchenStage";
			break;
	}
	
	auto backgroundImage = Sprite::create("images/" + type + ".png");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	backgroundImage->setScale(visibleSize.width / backgroundImage->getContentSize().width, visibleSize.height / backgroundImage->getContentSize().height);
	backgroundImage->setAnchorPoint(Point::ZERO);
	this->addChild(backgroundImage, 0);
}

void GameScene::MakeUI() {
	UI = new GameSceneUI();
	this->addChild(UI->jumpButton, 100);
	this->addChild(UI->stopButton, 100);
	this->addChild(UI->healthLabel, 100);
	this->addChild(UI->healthBar, 101);
	this->addChild(UI->healthBarBackground, 100);
	this->addChild(UI->scoreText, 100);

	UI->pauseButton->setCallback(CC_CALLBACK_0(GameScene::OnClickPause, this));
	auto menu = Menu::create(UI->pauseButton, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 100);
}

// 과일 생성
void GameScene::MakeFruit() {
	string fruitType = UserDefault::getInstance()->getStringForKey("selectedFruit");
	fruit = new Fruit(fruitType);
	this->addChild(fruit->fruitImage, 10);
	this->addChild(fruit->stopLable, 10);
	fruit->Rotate();
}

// 오브젝트(장애물, 물방울) 생성
void GameScene::MakeObject() {
	waterdrop = new Waterdrop();
	this->addChild(waterdrop->waterdropImage, 5);
	obstacleMap.insert(make_pair("Bottle", new Obstacle("Bottle")));
	obstacleMap.insert(make_pair("Coke", new Obstacle("Coke")));
	obstacleMap.insert(make_pair("Fork", new Obstacle("Fork")));
	obstacleMap.insert(make_pair("Knife", new Obstacle("Knife")));
	this->addChild(obstacleMap["Bottle"]->obstacleImage, 5);
	this->addChild(obstacleMap["Coke"]->obstacleImage, 5);
	this->addChild(obstacleMap["Fork"]->obstacleImage, 5);
	this->addChild(obstacleMap["Knife"]->obstacleImage, 5);

	board1 = new Board();
	board2 = new Board();
	board1->boardImage->setPositionX(board1->width * 0.5);
	this->addChild(board1->boardImage, 1);
	this->addChild(board2->boardImage, 1);
}

void GameScene::MoveObject() {
	srand(time(NULL));
	int r = rand() % 5;
	
	switch (r)
	{
		case 0:
			waterdrop->StopEnd();
			break;
		case 1:
			obstacleMap["Bottle"]->StopEnd();
			break;
		case 2:
			obstacleMap["Coke"]->StopEnd();
			break;
		case 3:
			obstacleMap["Fork"]->StopEnd();
			obstacleMap["Fork"]->Fall();
			break;
		case 4:
			obstacleMap["Knife"]->StopEnd();
			obstacleMap["Knife"]->Fall();
			break;
		default:
			break;
	}
}

// 오브젝트 자동삭제
void GameScene::DeleteObject() {
	if (waterdrop->CheckNeedDelete()) {
		waterdrop->Stop();
		waterdrop->Remove();
		MoveObject();
	}
	
	for (pair<string, Obstacle*> obstacle : obstacleMap) {
		if (obstacle.second->CheckNeedDelete()) {
			obstacle.second->Stop();
			obstacle.second->Remove();
			MoveObject();
		}
	}
	
	if (board1->CheckNeedDelete()) {
		board1->Remove();
	}
	
	if (board2->CheckNeedDelete()) {
		board2->Remove();
	}
}

// 충돌 체크
void GameScene::CheckCollide() {
	auto waterdropBoundingbox = waterdrop->waterdropImage->getBoundingBox();
	if (waterdropBoundingbox.intersectsCircle(fruit->fruitImage->getPosition(), fruit->fruitRadius)) {
		experimental::AudioEngine::play2d("sounds/Waterdrop.mp3");
		waterdrop->Remove();
		waterdrop->Stop();
		MoveObject();
		score++;
		if(fullHP>health)
		    health++;
		UI->UpdateInfo((health * 100) / fullHP, score);
	}

	for (pair<string, Obstacle*> obstacle : obstacleMap) {
		if (obstacle.second->moving) {
			auto obstacleBoundingbox = obstacle.second->obstacleImage->getBoundingBox();

			if (obstacleBoundingbox.intersectsCircle(fruit->fruitImage->getPosition(), fruit->fruitRadius) && !collided) {
				health-=10;
				fruit->PlayAnimation();
				collided = true;
				UI->UpdateInfo((health * 100) / fullHP, score);
				if (health <= 0 && !end) {
					end = true;
					GameOver();
				}
			}
			if (!obstacleBoundingbox.intersectsCircle(fruit->fruitImage->getPosition(), fruit->fruitRadius) && collided) {
				collided = false;
			}
		}
	}
}

void GameScene::Resume() {
	experimental::AudioEngine::resumeAll();

	fruit->fruitImage->resume();
	board1->boardImage->resume();
	board2->boardImage->resume();
	waterdrop->waterdropImage->resume();
	for (pair<string, Obstacle*> o : obstacleMap) {
		if (o.second->moving)
			o.second->obstacleImage->resume();
	}
	paused = false;
}

void GameScene::Restart() {
	experimental::AudioEngine::stopAll();
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void GameScene::GameOver() {
	if (board1->stopping) {
		fruit->stopLable->setVisible(false);
		fruit->StopEnd();
		board1->StopEnd();
		board2->StopEnd();
		if (waterdrop->moving)
			waterdrop->StopEnd();
		for (pair<string, Obstacle*> o : obstacleMap) {
			if (o.second->moving)
				o.second->StopEnd();
		}
	}
	experimental::AudioEngine::pauseAll();

	fruit->fruitImage->pause();
	board1->boardImage->pause();
	board2->boardImage->pause();
	waterdrop->waterdropImage->pause();
	for (pair<string, Obstacle*> o : obstacleMap) {
		if (o.second->moving)
			o.second->obstacleImage->pause();
	}

	auto gopu = GameoverPopup::create();
	gopu->GetInfo(score);
	this->addChild(gopu, 110);

	int waterdropScore = score + UserDefault::getInstance()->getIntegerForKey("waterdrop");
	UserDefault::getInstance()->setIntegerForKey("waterdrop", waterdropScore);

	int bestScore = UserDefault::getInstance()->getIntegerForKey("bestScore");
	if (bestScore < score) {
		UserDefault::getInstance()->setIntegerForKey("bestScore", score);
	}

	UserDefault::getInstance()->flush();
}

void GameScene::GoMain() {
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
}
