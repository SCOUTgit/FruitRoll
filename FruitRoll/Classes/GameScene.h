#pragma once
#include "cocos2d.h"
#include "Fruit.h"
#include "Obstacle.h"
#include "Waterdrop.h"
#include "Board.h"
#include "GameSceneUI.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;
USING_NS_CC;

class GameScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	int playTime;									// 생존 시간
	int score;										// 점수
	int money;										// 획득한 물방울
	int health;										// 체력
	bool collided;									// 충돌 중인지 체크
	bool end;										// 게임이 끝났는지 체크
	string backgroundType;							// 배경의 종류
	Sprite* backgroundImage;						// 배경의 이미지
	Fruit* fruit;									// 과일
	Waterdrop* waterdrop;							// 물방울
	unordered_map<string, Obstacle*> obstacleMap;	// 장애물 
	Board* board1;									// 나무판자1
	Board* board2;									// 나무판자2
	GameSceneUI* UI;								// 게임씬 UI

	void Tick(float f);								// 한 프레임마다 호출
	void Jump();									// 점프버튼이 눌렸을 때
	void MakeBackground();							// 배경 생성
	void MakeUI();									// UI 생성
	void MakeFruit();								// 과일 생성
	void MakeObject();								// 오브젝트 생성
	void MoveObject();								// 오브젝트 이동
	void DeleteObject();							// 오브젝트 삭제
	void CheckCollide();							// 충돌 체크
	void GameOver();								// 게임 오버

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event *unused_event);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};