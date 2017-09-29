#ifndef _MovieBack_h_
#define _MovieBack_h_

#include "cocos2d.h"
#include <vector>
#include "ScrollSprite.h"

class MovieBack : public ScrollSprite
{
public:
	bool init();
	static MovieBack* create();
	std::vector<cocos2d::Sprite*> _bgSprites;
	float _scrollSpeed;
};

#endif