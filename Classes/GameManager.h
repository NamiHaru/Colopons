#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "MapCreator.h"
#include "TitleSelectScene.h"
#include "SaveData.h"
#include "Button.h"
#include "ColorEnum.h"
#include "EndingScene.h"

USING_NS_CC;

#define MAX_LIFE 3
#define START_COUNT 3

class GameManager :public Node 
{
public:

	static GameManager* create(int num);
	bool init(int num);
	void update(float delta);

	bool standbyAnimation();
	bool startAnimation();
	bool stopAnimation();
	bool missAnimation();
	void lifeAnimation();

	void StayShowMessage(int num);
	void StayCloseMessage();


	void dispLife(int life,int max);
	void dispGoal();
	void checkGoalSprite();


	SaveData* user;
	MapCreator* map;
	bool* isGoal;
	bool isTouched;
	Color4F stageColor;
	GAMESTATE gameState;
	Sprite* messageSp;
	Vector<Sprite*> lifeSps;
	int playerLife,maxLife;

	int animationCount;//カウントダウンに用いる

	float timer;


	//プレイヤーの操作が異なるので仮想化
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);


};


#endif // !__GAME_MANAGER_H__
