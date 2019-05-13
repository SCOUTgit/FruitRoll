#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;
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
	ui::LoadingBar* healthBar;				// 체력 게이지
	Sprite* healthBarBackground;			// 체력 게이지 배경
	ui::Text* scoreText;					// 획득한 물방울
	Size visibleSize;						// 해상도

	void MakeButton();						// 버튼 생성
	void MakeInfo();						// 정보 화면 생성
	void UpdateInfo(int hp, int score);		// 정보 업데이트
};