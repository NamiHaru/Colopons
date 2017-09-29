#ifndef _Movie3_h_
#define _Movie3_h_

#include "cocos2d.h"
#include "CharacterAnimation.h"

class Movie3 : public cocos2d::Layer
{
public:
	static Movie3* create();
	bool init();
	void update(float delta);
	static cocos2d::Scene* createScene();
	CharacterAnimation* _charAnim;
	CharacterAnimation* _char2;
	cocos2d::Vec2 bezier(float per, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 po2);
	void drawBezier(cocos2d::DrawNode* dn, int seg, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 pos2);
	cocos2d::Vec2 _bezierPos[3];
};

#endif // !_Movie3_h_
