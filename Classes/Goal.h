#ifndef __GOAL_H__
#define __GOAL_H__

#include "cocos2d.h"
#include"ObjectBase.h"

USING_NS_CC;

//ìGÇÃäÓñ{évçl
class Goal :public ObjectBase 
{
private:
	float animationTimer, goalTimer;
	DrawNode* draw;
	Color4F myColor;
	bool* isGoal;
	Sprite* mySprite;
	Sprite* mask;
public:
	static Goal* create(Vec2 spawnPos,Color4F color);
	virtual bool init(Vec2 spawnPos,Color4F color);
	void update(float delta);

	Color4F getStageColor();
	float getAnimationScale();
	void stopAnimation();
	bool drawGoalAction();
	void setisGoalAddress(bool* is);
};

#endif // !__GOAL_H__
