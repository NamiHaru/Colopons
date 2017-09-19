#ifndef _TitleCharacter_h_
#define _TitleCharacter_h_

#include "cocos2d.h"
#include "CharacterAnimation.h"

class TitleCharacter : public cocos2d::Sprite
{
public:
	bool init();
	static TitleCharacter* create();
	cocos2d::Animation* anim;
	void update(float delta);
	void setColor(cocos2d::Color3B color);
private:
	float _timer = 0.0f;
	CharacterAnimation* _charAnim;
	enum eSTATE
	{
		MOVE,
		STAND,
		JUMP
	};
	eSTATE _state;
	void changeState();
	float _walkTime = 0.3f;
};

#endif // !_TitleCharacter_h_
