#ifndef _MenuTable_h_
#define _MenuTable_h_

#include "cocos2d.h"

class MenuTable : public cocos2d::Sprite
{
public:
	static MenuTable* createInOpened(const cocos2d::String path, cocos2d::Vec2 defaultPos, float openScale = 1.0f, float scalingTime = 1.0f);
	static MenuTable* createInClosed(const cocos2d::String path, cocos2d::Vec2 defaultPos, float closeScale = 0.0f, float scalingTime = 1.0f);
	bool init();

	void setOpenScale(float scale);
	void setCloaseScale(float scale);
	void setOpenPos(float x, float y);
	void setOpenPos(cocos2d::Vec2 pos);
	void setClosePos(float x, float y);
	void setClosePos(cocos2d::Vec2 pos);

	void openMenu();
	void closeMenu();

private:
	cocos2d::Vec2 _openPos = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 _closePos = cocos2d::Vec2::ZERO;

	float _closeScale = 0.0f;
	float _openScale = 1.0f;

	float _scalingTime;
	float _timer = 0.0f;

	bool _isScaling = false;
	bool _runMode;

	void openingMenu(float delta);
	void closingMenu(float delta);
};

#endif // !_MenuTable_h_
