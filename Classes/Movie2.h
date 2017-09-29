#ifndef _Movie2_h_
#define _Movie2_h_

#include "cocos2d.h"
#include <vector>
#include "CharacterAnimation.h"

class Movie2 : public cocos2d::Layer
{
public:
	static Movie2* create();
	bool init();
	void update(float delta);
	static cocos2d::Scene* createScene();
	CharacterAnimation* _charAnim;
};

#endif