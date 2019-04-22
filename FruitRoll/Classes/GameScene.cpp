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
	this->schedule(schedule_selector(GameScene::MakeObject), 3);
	this->schedule(schedule_selector(GameScene::Tick));
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/bgm.wav", true);
	
	return true;
}

void GameScene::Tick(float f) {
	DeleteObject();
	CheckCollide();
	for (auto board : boardList) {
		if (board->CheckNeedMake())
			MakeBoard();
	}
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

	MakeBoard();
	MakeBoard();
	boardList.front()->boardImage->setPosition(boardList.front()->boardImage->getContentSize().width / 2, 200);
	boardList.front()->madeBoard = true;
}

// 과일 추가
void GameScene::MakeFruit() {
	fruit = new Fruit("Apple");
	this->addChild(fruit->fruitImage, 10);
	fruit->Rotate();
}

// 오브젝트(장애물, 물방울) 자동생성
void GameScene::MakeObject(float f) {
	// 랜덤으로 오브젝트의 종류 설정 1. 물방울 2. 움직이는 장애물 3. 떨어지는 장애물
	srand(time(NULL));
	int random = rand() % 3;

	Waterdrop* waterdrop;
	Obstacle* obstacle;

	switch (random) {
	case 0:
		waterdrop = new Waterdrop();
		this->addChild(waterdrop->waterdropImage, 2);
		waterdropList.push_back(waterdrop);
		break;
	case 1:
		obstacle = new Obstacle("Fixed");
		this->addChild(obstacle->obstacleImage, 2);
		obstacleList.push_back(obstacle);
		break;
	case 2:
		obstacle = new Obstacle("Falling");
		this->addChild(obstacle->obstacleImage, 2);
		obstacleList.push_back(obstacle);
		break;
	}
}

// 오브젝트 자동삭제
// 좌표 끝까지 움직였을 때 삭제
void GameScene::DeleteObject() {
	if (!waterdropList.empty() && waterdropList.front()->CheckNeedDelete()) {
		this->removeChild(waterdropList.front()->waterdropImage);
		delete waterdropList.front();
		waterdropList.pop_front();
	}
	if (!obstacleList.empty() && obstacleList.front()->CheckNeedDelete()) {
		this->removeChild(obstacleList.front()->obstacleImage);
		delete obstacleList.front();
		obstacleList.pop_front();
	}
	if (!boardList.empty() && boardList.front()->CheckNeedDelete()) {
		this->removeChild(boardList.front()->boardImage);
		delete boardList.front();
		boardList.pop_front();
	}
}

// 나무판자 생성
// 나무판자 리스트의 첫번째 스프라이트가 0에 접근했을 때 호출
void GameScene::MakeBoard() {
	Board* board = new Board();
	this->addChild(board->boardImage, 1);
	boardList.push_back(board);
}

// 충돌 체크
void GameScene::CheckCollide() {
	auto fruitBoundingbox = fruit->fruitImage->getBoundingBox();
	for (list<Waterdrop*>::iterator i = waterdropList.begin(); i != waterdropList.end();) {
		auto waterdropBoundingbox = (*i)->waterdropImage->getBoundingBox();
		if (fruitBoundingbox.intersectsRect(waterdropBoundingbox)) {
			SimpleAudioEngine::sharedEngine()->playEffect("sounds/waterdrop.wav");
			score++;
			this->removeChild((*i)->waterdropImage);
			delete *i;
			i = waterdropList.erase(i);
		}
		else
			i++;
	}

	for (Obstacle* obstacle : obstacleList) {
		auto obstacleBoundingbox = obstacle->obstacleImage->getBoundingBox();
		if (fruitBoundingbox.intersectsRect(obstacleBoundingbox)) {
			health--;
			fruit->PlayAnimation();
		}
	}
}