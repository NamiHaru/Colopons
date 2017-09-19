#ifndef _TitleBackground_h_
#define _TitleBackground_h_

#include "cocos2d.h"
#include <vector>
#include "ScrollSprite.h"

class TitleBackground : public cocos2d::Sprite
{
public:
	bool init(int clearedStage);
	static TitleBackground* create(int clearedStage);
	std::vector<cocos2d::Sprite*> _bgSprites;
};

#endif