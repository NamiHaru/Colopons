#ifndef _Tulip_h_
#define _Tulip_h_

#include "cocos2d.h"

class Tulip : public cocos2d::Sprite
{
public:
	bool init(cocos2d::SpriteFrame* flower, cocos2d::SpriteFrame* leaf, int clearedStage);
	static Tulip* create(cocos2d::SpriteFrame* flower, cocos2d::SpriteFrame* leaf, int clearedStage);
	cocos2d::Sprite* _flower;
	cocos2d::Sprite* _leaf;

	void update(float delta);
};
#endif // !_Tulip_h_
