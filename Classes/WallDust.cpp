#include "WallDust.h"

WallDust* WallDust::create(Vec2* vects, int segment, Color4F color) 
{
	WallDust *pRet = new WallDust();
	if (pRet && pRet->init(vects,segment,color))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool WallDust::init(Vec2* vects, int segment, Color4F color) 
{
	if (!Node::init())return false;

	timer = 1.0f;
	myColor = color;
	seg = segment;

	//í∏ì_ç¿ïWê›íË
	for (int i = 0; i < segment; i++) {
		//log("minus-[%0.0f,%0.0f]", vects[i].x, vects[i].y);
		myVects.push_back(vects[i]);
	}
	dDust= DrawNode::create();
	addChild(dDust);
	dDust->drawPolygon(&myVects[0], seg, myColor, 4, Color4F::BLACK);

	scheduleUpdate();
	
	return true;
};

void WallDust::update(float delta)
{
	timer -= 0.01f;

	dDust->clear();
	dDust->drawPolygon(&myVects[0], seg, Color4F(myColor.r,myColor.g,myColor.b,timer), 4, Color4F::BLACK);

	if (timer < 0)removeFromParentAndCleanup(true);

};
