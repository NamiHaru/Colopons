#ifndef _SelectBackground_h_
#define _SelectBackground_h_

#include "cocos2d.h"

class SelectBackground : public cocos2d::Node
{
public:
	static SelectBackground* create(cocos2d::Color4F color = cocos2d::Color4F::WHITE);
	bool init(cocos2d::Color4F color);
};

#endif