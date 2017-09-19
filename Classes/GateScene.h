#ifndef __GATE_SCENE_H__
#define __GATE_SCENE_H__

#include "cocos2d.h"
#include "TitleSelectScene.h"
#include "MainGameScene.h"

USING_NS_CC;

class GateScene :public Scene 
{
public:
	static GateScene* createScene();
	bool init();

	bool onTouchBegan(const Touch * touch, Event *unused_event);
	void onTouchMoved(const Touch * touch, Event *unused_event);
	void onTouchEnded(const Touch * touch, Event *unused_event);

};


#endif // !__GATE_SCENE_H__
