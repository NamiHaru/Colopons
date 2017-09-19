#ifndef _EndTitle_h_
#define _EndTitle_h_

#include "cocos2d.h"

class EndTitle : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(EndTitle);
	void update(float delta);

private:
	cocos2d::Sprite* _map;

	float _timer = -3.0f;
	const float _STOP_TIME = 3.0f;
	const float _MOVE_TIME = 1.5f;
	int _diff = 1;
	int _cnt = 0;
	const int _COUNT = 7;
};

#endif // !_EndTitle_h_
