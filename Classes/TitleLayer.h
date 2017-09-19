#ifndef _TitleLayer_h_
#define _TitleLayer_h_

#include "cocos2d.h"
#include "TitleBackground.h"
#include "TitleScroll.h"
#include "WoodScroll.h"
#include "SaveData.h"

class TitleLayer : public cocos2d::Layer
{
public:
	bool init(SaveData* saveData);
	static TitleLayer* create(SaveData* saveData);
	TitleBackground* tbg;
	bool _replacedScene;
	TitleScroll* ts;
	WoodScroll* ws;
	float _woodScrollSpeed = 1.2f;
	float _scrollSpeed = 3.0f;
	cocos2d::Color4F _lastClearColor = cocos2d::Color4F::WHITE;
	SaveData* _saveData;

	void setScrollStop();
	void setDefaultSpeed();
	
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	//cocos2d::Label* label;
};

#endif