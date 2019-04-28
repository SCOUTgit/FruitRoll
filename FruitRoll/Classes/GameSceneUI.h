#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace ui;
USING_NS_CC;
 
class GameSceneUI
{
public:
	GameSceneUI();
	~GameSceneUI();

	Sprite* jumpButton;						// 점프 버튼
	Sprite* stopButton;						// 스탑 버튼
	MenuItemImage* pauseButton;				// 일시정지 메뉴아이템
	Label* healthLabel;						// 체력
	LoadingBar* healthBar;					// 체력 게이지 
	Label* waterdropLabel;					// 획득한 물방울
	Size visibleSize;						// 해상도

	void MakeButton();						// 버튼 생성
	void MakeInfo();						// 정보 화면 생성
	void UpdateInfo(int hp, int score);		// 정보 업데이트
};