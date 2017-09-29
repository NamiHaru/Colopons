#ifndef _Movie_h_
#define _MOvie_h_

#include "cocos2d.h"
#include "CharacterAnimation.h"
#include "MovieBack.h"

class Movie : public cocos2d::Layer
{
public:
	static Movie* create();
	bool init();
	void update(float delta);
	static cocos2d::Scene* createScene();
	CharacterAnimation* _charAnim;
	MovieBack* movieBack;
	void whiting(float delta);
	cocos2d::Sprite* mask;
};

#endif // !_Movie_h_
