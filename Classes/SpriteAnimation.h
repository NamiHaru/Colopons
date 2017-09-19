#ifndef _SpriteAnimation_h_
#define _SpriteAnimation_h_

#include "cocos2d.h"

class SpriteAnimation : public cocos2d::Node
{
public:
	bool init(std::string fileName, cocos2d::Size chipSize, float delay);
	static SpriteAnimation* create(std::string fileName, cocos2d::Size chipSize, float delay = 0.5f);

	void stopAnimation();
	void startAnimation();
private:
	cocos2d::Sprite* _mySprite;
	cocos2d::AnimationCache* _animationChache;
};

#endif // !_SpriteAnimation_h_
