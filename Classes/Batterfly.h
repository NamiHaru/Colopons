#ifndef _Batterfly_h_
#define _Batterfly_h_

#include "cocos2d.h"
#include "ColorEnum.h"

class Batterfly : public cocos2d::Sprite
{
public:
	bool init();
	static Batterfly* create();
	void update(float delta);
	float scaleRange(float f);

	//cocos2d::Sprite* _mySp;
	float _scaling;
	float _timer = 0.0f;
	int _dir = 1;

	float _speed = 5.0f;
	float _SWITCH_TIME = 0.6f;
};

#endif // !_Batterfly_h_
