#ifndef _ImageButton_h_
#define _ImageButton_h_

#include "cocos2d.h"

class ImageButton : public cocos2d::Sprite
{
public:
	bool init(bool strictJudgement);
	virtual void buttonPushed() = 0;
	// タッチイベント処理
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
protected:
	void _onButton();
	void _removeButton();
	cocos2d::Color3B color;
	cocos2d::String filePath;

	bool _isPressed = false;
	bool _strictJudgement;	// True : 一度指が離れたらダメ　False : 一度指が離れても位置を戻せばオッケー
};

#endif