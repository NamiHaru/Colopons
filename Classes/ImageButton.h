#ifndef _ImageButton_h_
#define _ImageButton_h_

#include "cocos2d.h"

class ImageButton : public cocos2d::Sprite
{
public:
	bool init(bool strictJudgement);
	virtual void buttonPushed() = 0;
	// �^�b�`�C�x���g����
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
protected:
	void _onButton();
	void _removeButton();
	cocos2d::Color3B color;
	cocos2d::String filePath;

	bool _isPressed = false;
	bool _strictJudgement;	// True : ��x�w�����ꂽ��_���@False : ��x�w������Ă��ʒu��߂��΃I�b�P�[
};

#endif