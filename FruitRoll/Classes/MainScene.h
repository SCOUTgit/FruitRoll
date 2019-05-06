#pragma once
#pragma execution_character_set("UTF-8")
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "GameScene.h"

using namespace std;
USING_NS_CC;

class MainScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	int bestScore;									// 최고점수
	int HP;											// 체력
	int waterdrop;									// 소유한 물방울
	string fruitType;								// 과일 타입
	ui::Text* HPText;								// 체력 텍스트
	ui::Text* waterdropText;						// 소유한 물방울 텍스트
	ui::Text* needWaterdropText;					// 체력강화에 필요한 물방울 텍스트
	Size visibleSize;								// 화면 사이즈
	Sprite* selectedSprite;							// 선택한 과일을 가리키는 스프라이트
	Menu* fruitMenu;								// 선택할 과일들이 있는 메뉴

	void MakeBackground();							// 배경 생성
	void MakeUI();									// UI 생성
	void Start();									// 게임 시작
	void SelectFruit(string type);					// 과일 선택
	void UpgradeHP();								// 체력 강화

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
};