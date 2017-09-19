#include "Batterfly.h"
#include <cmath>

using namespace cocos2d;
using namespace std;

bool Batterfly::init()
{
	if (!Sprite::init()) return false;
	
	_scaling = 0.1f;

	this->initWithFile("Title/Batterfly.png");
	this->setAnchorPoint(Vec2(0.5f,0.2f));

	this->scheduleUpdate();

	return true;
}

Batterfly* Batterfly::create()
{
	auto pRet = new Batterfly();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return pRet;
	}
}

void Batterfly::update(float delta)
{
	if (scaleRange(this->getScaleY()) == 0.0f)
	{
		_scaling = abs(_scaling);
	}
	else if (scaleRange(this->getScaleY()) == 1.0f)
	{
		_scaling = abs(_scaling) * -1;
	}
	this->setScaleY(this->getScaleY() + _scaling);

	_timer += delta;
	if (_timer > _SWITCH_TIME)
	{
		_dir *= -1;
		_timer = 0.0f;
	}
	this->setPositionY(this->getPositionY() + _dir*_speed);
}

float Batterfly::scaleRange(float f)
{
	if (f <= 0.0f) return 0.0f;
	if (f >= 1.0f) return 1.0f;
	return f;
}