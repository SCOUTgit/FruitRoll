#pragma once
#pragma execution_character_set("UTF-8")
#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class GameoverPopup :public Layer
{
public:

    static GameoverPopup * create();

    bool init();
    
    virtual void onEnter();
    virtual bool onTouchBegan(Touch* touch, Event* unused_event);
    virtual void onTouchMoved(Touch* touch, Event* unused_event);
    virtual void onTouchEnded(Touch* touch, Event *unused_event);
    
    void MakePopUp();
    void OnClickRestart();
    void OnClickGoMain();
    void GetInfo(int score);

public:

	string clickedButton;
	Sprite* restartButton;
	Sprite* goMainButton;
	ui::Text* scoreText;

	virtual void onEnter();
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event *unused_event);


	void MakePopUp();
	void OnClickRestart();
	void OnClickGoMain();
	void GetInfo(int score);
};
