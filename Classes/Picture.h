#ifndef _Picure_h_
#define _Picure_h_

#include "cocos2d.h"

class Picture : public cocos2d::Sprite
{
public:
	cocos2d::Sprite* _shadow;
	cocos2d::Sprite* _clip;
	int _stageID;
	cocos2d::Color3B _defaultColor;

	bool init(int id, bool cleared);
	static Picture* create(int id, bool cleared);

	void setPos(cocos2d::Vec2 pos);
	cocos2d::Vec2 getPos();

private:
	cocos2d::Vec2 _defaultPos;
};

#endif