#ifndef _ColorEnum_h_
#define _ColorEnum_h_

#include "cocos2d.h"

enum class eColor
{
	RED = 0,
	SKY,
	PURPLE,
	GREEN,
	ORANGE,
	BROWN,
	BLUE,
	PINK,
	INDIGO,
	YELLOW 
};

static cocos2d::Color3B getColorCode(eColor color)
{
	switch (color) {
	case eColor::RED:
		return cocos2d::Color3B(255, 36, 80);
		break;
	case eColor::SKY:
		return cocos2d::Color3B(110, 223, 255);
		break;
	case eColor::PURPLE:
		return cocos2d::Color3B(125, 31, 255);
		break;
	case eColor::GREEN:
		return cocos2d::Color3B(31, 157, 34);
		break;
	case eColor::ORANGE:
		return cocos2d::Color3B(255, 108, 0);
		break;
	case eColor::BROWN:
		return cocos2d::Color3B(164, 82, 0);
		break;
	case eColor::BLUE:
		return cocos2d::Color3B(13, 81, 255);
		break;
	case eColor::PINK:
		return cocos2d::Color3B(245, 135, 215);
		break;
	case eColor::INDIGO:
		return cocos2d::Color3B(23, 23, 128);
		break;
	case eColor::YELLOW:
		return cocos2d::Color3B(255, 242, 102);
		break;
	default:
		return cocos2d::Color3B(255, 255, 255);
		break;
	}
}

static cocos2d::Color3B getColorCode(int id)
{
	switch (id)
	{
	case 0:
		return cocos2d::Color3B(255, 36, 80);
		break;
	case 1:
		return cocos2d::Color3B(110, 223, 255);
		break;
	case 2:
		return cocos2d::Color3B(125, 31, 255);
		break;
	case 3:
		return cocos2d::Color3B(31, 157, 34);
		break;
	case 4:
		return cocos2d::Color3B(255, 108, 0);
		break;
	case 5:
		return cocos2d::Color3B(164, 82, 0);
		break;
	case 6:
		return cocos2d::Color3B(13, 81, 255);
		break;
	case 7:
		return cocos2d::Color3B(245, 135, 215);
		break;
	case 8:
		return cocos2d::Color3B(23, 23, 128);
		break;
	case 9:
		return cocos2d::Color3B(255, 242, 102);
		break;
	default:
		return cocos2d::Color3B(255, 255, 255);
		break;
	}
}

#endif // !_ClorEnum_h_
