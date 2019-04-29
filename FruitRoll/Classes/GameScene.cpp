#include "GameScene.h"

Scene* GameScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene::create();
	
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	backgroundType = "KitchenStage";
	health = 10;
	score = 0;
	fullHP = health;

	MakeFruit();
	MakeBackground();
	MakeObject();
	MakeUI();
	MoveObject();

	int bgmID = experimental::AudioEngine::play2d("sounds/bgm.wav", true);
	experimental::AudioEngine::preload("sounds/waterdrop.wav");
	this->schedule(schedule_selector(GameScene::Tick));

	return true;
}

void GameScene::Tick(float f) {
	DeleteObject();
	CheckCollide();
}


void GameScene::onEnter() {
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onExit() {
	_eventDispatcher->removeAllEventListeners();
	experimental::AudioEngine::uncacheAll();
	Layer::onExit();
}


void GameScene::Jump() {
	if(!fruit->jumping)
		fruit->Jump();
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event) {
	auto touchPoint = touch->getLocation();
	
	if (UI->jumpButton->getBoundingBox().containsPoint(touchPoint) && !fruit->jumping) {
		fruit->Jump();
		experimental::AudioEngine::play2d("sounds/waterdrop.wav");

		UI->jumpButton->setOpacity(128);
	}

	else if (UI->stopButton->getBoundingBox().containsPoint(touchPoint) && !fruit->jumping) {
		fruit->Stop();
		board1->Stop();
		board2->Stop();
		waterdrop->Stop();
		for (pair<string,Obstacle*> o : obstacleMap) {
			o.second->Stop();
		}
		UI->stopButton->setOpacity(128);
	}

	return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* unused_event) {
	auto touchPoint = touch->getLocation();
	if (UI->stopButton->getBoundingBox().containsPoint(touchPoint) && !fruit->jumping) {
		fruit->Stop();
		board1->Stop();
		board2->Stop();
		waterdrop->Stop();
		for (pair<string, Obstacle*> o : obstacleMap) {
			o.second->Stop();
		}
		UI->stopButton->setOpacity(128);
	}
}

void GameScene::onTouchEnded(Touch* touch, Event *unused_event) {
	auto touchPoint = touch->getLocation();
	if (board1->stopping) {
		fruit->StopEnd();
		board1->StopEnd();
		board2->StopEnd();
		if (waterdrop->moving)
			waterdrop->StopEnd();
		for (pair<string, Obstacle*> o : obstacleMap) {
			if(o.second->moving)
				o.second->StopEnd();
		}
	}
	UI->jumpButton->setOpacity(255);
	UI->stopButton->setOpacity(255);
}

// 배경 추가
void GameScene::MakeBackground() {
	// sceneType 정하기
	backgroundImage = Sprite::create("images\\" + backgroundType + ".png");
	backgroundImage->setAnchorPoint(Point::ZERO);

	// 화면에 맞춰서 배경의 크기 조절하기
	auto visibleSize = Director::getInstance()->getVisibleSize();
	backgroundImage->setScale(visibleSize.width / backgroundImage->getContentSize().width, visibleSize.height / backgroundImage->getContentSize().height);

	this->addChild(backgroundImage, 0);
}

void GameScene::MakeUI() {
	UI = new GameSceneUI();
	this->addChild(UI->jumpButton, 100);
	this->addChild(UI->stopButton, 100);
	this->addChild(UI->pauseButton, 100);
	this->addChild(UI->healthLabel, 100);
	this->addChild(UI->healthBar, 101);
	this->addChild(UI->healthBarBackground, 100);
	this->addChild(UI->scoreText, 100);
}

// 과일 생성
void GameScene::MakeFruit() {
	fruit = new Fruit("Apple");
	this->addChild(fruit->fruitImage, 10);
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
	board1->boardImage->setPosition(board1->width * 0.5, board1->height * 1.5);
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
// 좌표 끝까지 움직였을 때 삭제
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
		waterdrop->Remove();
		waterdrop->Stop();
		MoveObject();
		score++;
		UI->UpdateInfo((health * 100) / fullHP, score);
	}

	for (pair<string, Obstacle*> obstacle : obstacleMap) {
		if(obstacle.second->moving){
			auto obstacleBoundingbox = obstacle.second->obstacleImage->getBoundingBox();
		
			if (obstacleBoundingbox.intersectsCircle(fruit->fruitImage->getPosition(), fruit->fruitRadius) && !collided) {
				health--;
				fruit->PlayAnimation();
				collided = true;
				UI->UpdateInfo((health * 100) / fullHP, score);
			}
			if (!obstacleBoundingbox.intersectsCircle(fruit->fruitImage->getPosition(), fruit->fruitRadius) && collided) {
				collided = false;
			}
		}
	}
}