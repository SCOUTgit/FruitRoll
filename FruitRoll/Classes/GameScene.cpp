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

	MakeFruit();
	makeBackground();
	MakeObject();
	MoveObject();

	this->schedule(schedule_selector(GameScene::Tick));
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/bgm.wav", true);

	return true;
}

void GameScene::Tick(float f) {
	DeleteObject();
	CheckCollide();
}

// 배경 추가
void GameScene::makeBackground() {
	// sceneType 정하기
	backgroundImage = Sprite::create("images\\" + backgroundType + ".png");
	backgroundImage->setAnchorPoint(Point::ZERO);

	// 화면에 맞춰서 배경의 크기 조절하기
	auto visibleSize = Director::getInstance()->getVisibleSize();
	backgroundImage->setScale(visibleSize.width / backgroundImage->getContentSize().width, visibleSize.height / backgroundImage->getContentSize().height);

	this->addChild(backgroundImage, 0);
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
	this->addChild(board1->boardImage, 1);
	board1->boardImage->setPosition(board1->boardImage->getContentSize().width / 2, 200);
	board2 = new Board();
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
		break;
	case 4:
		obstacleMap["Knife"]->StopEnd();
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
			obstacle.second->Remove(obstacle.first);
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
		SimpleAudioEngine::sharedEngine()->playEffect("sounds/waterdrop.wav");
		waterdrop->Remove();
		waterdrop->Stop();
		MoveObject();
		score++;
	}

	for (pair<string, Obstacle*> obstacle : obstacleMap) {
		auto obstacleBoundingbox = obstacle.second->obstacleImage->getBoundingBox();

		if (obstacleBoundingbox.intersectsCircle(fruit->fruitImage->getPosition(), fruit->fruitRadius) && !collided) {
			health--;
			fruit->PlayAnimation();
			collided = true;
		}
		if (!obstacleBoundingbox.intersectsCircle(fruit->fruitImage->getPosition(), fruit->fruitRadius) && collided) {
			collided = false;
		}
	}
}