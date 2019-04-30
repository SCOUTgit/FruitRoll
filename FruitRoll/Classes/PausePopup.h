#pragma once
#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class PausePopup :public Layer
{
public:

    static PausePopup * create();

    bool init();

    virtual void onEnter();

    bool onTouchBegan(Touch* touch, Event* event);

	void MakePopUp();
	void OnClickResume(Ref* object);
	void OnClickRestart(Ref* object);
	void OnClickGoMain(Ref* object);
};