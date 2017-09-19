#ifndef _EndStart_h_
#define _EndStart_h_

#include "cocos2d.h"
#include "Wood.h"
#include "EndingCharacterAnimation.h"

class EndStart : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(EndStart);

	cocos2d::Sprite* _upSp;
	cocos2d::Sprite* _downSp;

	cocos2d::Sprite* _woodShadow[8];
	Wood* _wood[8];
	cocos2d::Sprite* _charaShadow[6];
	EndingCharacterAnimation* _chara[6];
};

#endif // !_EndStart_h_
#pragma once
