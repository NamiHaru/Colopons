#ifndef _EndOpen_h_
#define _EndOpen_h_

#include "cocos2d.h"

class EndOpen : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(EndOpen);

	cocos2d::Sprite* _leftWall;
	cocos2d::Sprite* _rightWall;
	cocos2d::Sprite* _light;
};
#endif // !_EndOpen_h_
