#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class MainScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
};