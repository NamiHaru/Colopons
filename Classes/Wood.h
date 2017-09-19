#ifndef _Wood_h_
#define _Wood_h_

#include "cocos2d.h"
#include "ColorEnum.h"

class Wood : public cocos2d::Sprite
{
public:
	bool init(cocos2d::SpriteFrame* gr, cocos2d::SpriteFrame* br, int clearedStage);
	static Wood* create(cocos2d::SpriteFrame* gr, cocos2d::SpriteFrame* br, int clearedStage);

	cocos2d::Sprite* _bl;
	cocos2d::Sprite* _gr;
	cocos2d::Sprite* _br;

};

#endif // !_Wood_h_
