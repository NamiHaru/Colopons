#ifndef _WoodScroll_h_
#define _WoodScroll_h_

#include "cocos2d.h"
#include "ScrollSprite.h"

class WoodScroll : public ScrollSprite
{
public:
	static WoodScroll* create(float scrollSpeed, int clearedStage);
	bool init(float scrollSpeed, int clearedStage);
};

#endif // !_WoodScroll_h_
