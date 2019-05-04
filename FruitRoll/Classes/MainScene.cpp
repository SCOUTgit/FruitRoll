#include "MainScene.h"

Scene* MainScene::createScene() {
	auto scene = Scene::create();
	auto layer = MainScene::create();

	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}