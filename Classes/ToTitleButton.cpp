#include "ToTitleButton.h"

using namespace cocos2d;

bool ToTitleButton::init(Color3B color, bool lookedSky)
{
	if (!Sprite::init()) return false;
	this->initWithFile("Select/ToTitle.png");
	this->setColor(color);

	if (!lookedSky)
	{
		_shadow = Sprite::create("Select/ToTitleShadow.png");
		_shadow->setColor(color);
		_shadow->setZOrder(-1);
		_shadow->setPosition(this->getContentSize()*0.5f);
		this->addChild(_shadow);

		//this->scheduleUpdate();
	}

	return true;
}

ToTitleButton* ToTitleButton::create(Color3B color, bool lookedSky)
{
	ToTitleButton* pRet = new ToTitleButton();
	if (pRet && pRet->init(color, lookedSky))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void ToTitleButton::update(float delta)
{
	_timer += delta;
	_volume = adjustRange(_timer / _SWITCH_TIME);
	if (_dir < 0) _volume = 1 - _volume;

	_shadow->setScale((_MAX_SCALE - _MIN_SCALE) * _volume + _MIN_SCALE);
	_shadow->setOpacity(adjustOpacity(_volume));

	if (_timer > _SWITCH_TIME)
	{
		_dir *= -1;
		_timer = 0.0f;
	}
}

float ToTitleButton::adjustRange(float f)
{
	if (f <= 0.0f) return 0.0f;
	if (f >= 1.0f) return 1.0f;
	return f;
}

float ToTitleButton::adjustOpacity(float f)
{
	return f * 255;
}

void ToTitleButton::startToShine()
{
	this->scheduleUpdate();
}