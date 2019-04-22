#pragma once
#include "cocos2d.h"
#include "Fruit.h"
#include "Obstacle.h"
#include "Waterdrop.h"
#include "Board.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;
USING_NS_CC;

class GameScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	int playTime;						// 생존 시간
	int score;							// 점수
	int money;							// 획득한 물방울
	int health;							// 체력
	string backgroundType;				// 배경의 종류
	Sprite* backgroundImage;			// 배경의 이미지
	Fruit* fruit;						// 과일
	list<Waterdrop*> waterdropList;		// 물방울 리스트
	list<Obstacle*> obstacleList;		// 장애물 리스트
	list<Board*> boardList;				// 나무판자 리스트

	void Tick(float f);					// 한 프레임마다 호출
	void makeBackground();				// 배경 생성
	void MakeFruit();					// 과일 생성
	void MakeObject(float f);			// 오브젝트 자동생성
	void MakeBoard();					// 나무판자 생성
	void DeleteObject();				// 오브젝트 삭제
	void PrintInfo();					// 정보 출력
	void RunAudio();					// 오디오 실행
	void CheckCollide();				// 충돌 체크

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};