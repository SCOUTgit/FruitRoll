#pragma once
#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class GameoverPopup :public Layer
{
public:

    static GameoverPopup * create();

    bool init();

    virtual void onEnter();

	bool onTouchBegan(Touch* touch, Event* event);

	void MakePopUp();
	void OnClickRestart(Ref* object);
	void OnClickGoMain(Ref* object);
	void GetInfo(int score);

	ui::Text* scoreText;
};