#include "MainGameScene.h"


MainGameScene* MainGameScene::createScene(int num)
{
	MainGameScene *pRet = new MainGameScene();
	if (pRet && pRet->init(num))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
};

bool MainGameScene::init(int num) 
{
	if (!Scene::init()) 
	{
		return false;
	}

	gm = GameManager::create(num);
	addChild(gm,5);

	gameLayer = gm->map->printMap();
	addChild(gameLayer,1);

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/GameBGM.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/GameBGM.mp3");

	return true;
};
