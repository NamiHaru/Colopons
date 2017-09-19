#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class MainGameScene :public Scene 
{
public:
	static MainGameScene* createScene(int num);
	bool init(int num);

	GameManager* gm;
	Layer* gameLayer;


};

#endif //!__MAIN_GAME_SCENE_H__

