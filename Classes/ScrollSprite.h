#ifndef _ScrollSprite_h_
#define _ScrollSprite_h_

#include "cocos2d.h"
#include <vector>

class ScrollSprite : public cocos2d::Node
{
public:
	enum eOrientation
	{
		landscape,	// 横
		portrait	// 縦
	};

	static ScrollSprite* create(std::string fileName, float scrollSpeed, eOrientation orientation = landscape, cocos2d::Color3B color = cocos2d::Color3B::WHITE);
	
	bool init(std::string fileName, float scrollSpeed, eOrientation orientation, cocos2d::Color3B color);
	//void update(float delta);
	void updateL(float delta);
	void updateP(float delta);
	void setScrollSpriteSpeed(float speed);	// スクロールスピード変更

	std::vector<cocos2d::Node*> _bgSprites;
	float _scrollSpeed;
};

#endif