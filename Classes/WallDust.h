#ifndef __WALLDUST_H__
#define __WALLDUST_H__

#include "cocos2d.h"

USING_NS_CC;

class WallDust :public Node 
{
public:
	static WallDust* create(Vec2* vects, int segment, Color4F color);
	bool init(Vec2* vects, int segment, Color4F color);

	void update(float delta);

	std::vector<Vec2> myVects;
	float timer;
	DrawNode* dDust;
	int seg;
	Color4F myColor;

};

#endif // !__WALLDUST_H__
