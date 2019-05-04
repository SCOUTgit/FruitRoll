#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class MainScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
};