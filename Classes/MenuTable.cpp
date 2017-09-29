#include "MenuTable.h"

using namespace cocos2d;

MenuTable* MenuTable::createInOpened(const cocos2d::String path, cocos2d::Vec2 defaultPos, float openScale, float scalingTime)
{
	MenuTable* pRet = new MenuTable();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		pRet->_openPos = defaultPos;
		pRet->_closePos = defaultPos;
		pRet->_openScale = openScale;
		pRet->setScale(openScale);
		pRet->_scalingTime = scalingTime;
		pRet->initWithFile(path.getCString());
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

MenuTable* MenuTable::createInClosed(const cocos2d::String path, cocos2d::Vec2 defaultPos, float closeScale, float scalingTime)
{
	MenuTable* pRet = new MenuTable();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		pRet->_openPos = defaultPos;
		pRet->_closePos = defaultPos;
		pRet->_closeScale = closeScale;
		pRet->setScale(closeScale);
		pRet->_scalingTime = scalingTime;
		pRet->initWithFile(path.getCString());
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool MenuTable::init()
{
	if (!Sprite::init()) return false;

	return true;
}

void MenuTable::openMenu()
{
	if (_isScaling || this->getScale() == _openScale) return;
	_timer = 0.0f;
	this->schedule(schedule_selector(MenuTable::openingMenu));
}

void MenuTable::openingMenu(float delta)
{
	_isScaling = true;
	_timer += delta;

	if (_timer >= _scalingTime)
	{
		this->unschedule(schedule_selector(MenuTable::openingMenu));
		_timer = _scalingTime;
		_isScaling = false;
	}

	float n;
	if (_timer == 0) n = 0.0f;
	else n = _timer / _scalingTime;

	this->setScale((1 - n) * _closeScale + n * _openScale);
	this->setPositionX((1 - n) * _closePos.x + n * _openPos.x);
	this->setPositionY((1 - n) * _closePos.y + n * _openPos.y);
}

void MenuTable::closeMenu()
{
	if (_isScaling || this->getScale() == _closeScale) return;
	_timer = 0.0f;
	this->schedule(schedule_selector(MenuTable::closingMenu));
}

void MenuTable::closingMenu(float delta)
{
	_isScaling = true;
	_timer += delta;

	if (_timer >= _scalingTime)
	{
		this->unschedule(schedule_selector(MenuTable::closingMenu));
		_timer = _scalingTime;
		_isScaling = false;
	}

	float n;
	if (_timer == 0) n = 0.0f;
	else n = _timer / _scalingTime;

	this->setScale((1 - n) * _openScale + n * _closeScale);
	this->setPositionX((1 - n) * _openPos.x + n * _closePos.x);
	this->setPositionY((1 - n) * _openPos.y + n * _closePos.y);
}

void MenuTable::setOpenScale(float scale)
{
	_openScale = scale;
}

void MenuTable::setCloaseScale(float scale)
{
	_closeScale = scale;
}

void MenuTable::setOpenPos(float x, float y)
{
	_openPos = Vec2(x, y);
}

void MenuTable::setOpenPos(Vec2 pos)
{
	_openPos = pos;
}

void MenuTable::setClosePos(float x, float y)
{
	_closePos = Vec2(x, y);
}

void MenuTable::setClosePos(Vec2 pos)
{
	_closePos = pos;
}