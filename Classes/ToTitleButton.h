#ifndef _ToTitleButton_h_
#define _ToTitleButton_h_

#include "cocos2d.h"

class ToTitleButton : public cocos2d::Sprite
{
public:
	bool init(cocos2d::Color3B color, bool lookedSky);
	static ToTitleButton* create(cocos2d::Color3B color, bool lookedSky = true);
	void update(float delta);
	float adjustRange(float f);
	float adjustOpacity(float f);
	void startToShine();

	float _volume = 0.0f;
	float _timer = 0.0f;
	int _dir = 1;

	float _SWITCH_TIME = 0.5f;
	float _MIN_SCALE = 1.0f;
	float _MAX_SCALE = 1.5f;

	cocos2d::Sprite* _shadow;
};

#endif // !_ToTitleButton_h_
