#ifndef _TitleLogo_h_
#define _TitleLogo_h_

#include "cocos2d.h"

class TitleLogo : public cocos2d::Node
{
public:
	bool init(cocos2d::Color3B color);
	static TitleLogo* create(cocos2d::Color3B color = cocos2d::Color3B::WHITE);
private:
	cocos2d::Sprite* _logoSp;
	cocos2d::Sprite* _shadowSp;
};

#endif // !_TitleLogo_h_
