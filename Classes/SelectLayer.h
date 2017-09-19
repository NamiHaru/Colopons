#ifndef _SelectLayer_
#define _SelectLayer_

#include "cocos2d.h"
#include "ToTitleButton.h"
#include "SaveData.h"

class SelectLayer : public cocos2d::Layer
{
public:
	bool init(SaveData* saveData, cocos2d::Color4F color);
	static SelectLayer* create(SaveData* saveData, cocos2d::Color4F color = cocos2d::Color4F::WHITE);

	// タッチイベント処理
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	cocos2d::DrawNode* _dot;
	bool _isSceneReplace = false;
	bool _selectedButton = false;

	ToTitleButton* _toTitleButton;
	SaveData* _saveData;
};

#endif