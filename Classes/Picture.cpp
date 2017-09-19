#include "Picture.h"
#include "AllTags.h"
#include "ColorEnum.h"

using namespace cocos2d;

bool Picture::init(int id, bool cleared)
{
	if (!Sprite::init())
	{
		return false;
	}

	String* str;
	if(cleared) str = String::createWithFormat("Select/Cleared.png");
	else str = String::createWithFormat("Select/NotClear.png");

	//String* str = String::createWithFormat("Stage%f.png", id);
	
	this->initWithFile(str->getCString());

	if(cleared) _defaultColor = getColorCode(id);
	else _defaultColor = Color3B::GRAY;

	this->setColor(_defaultColor);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);

	_clip = Sprite::create("Select/Clip.png");
	_clip->setPosition(this->getContentSize().width*0.5f, this->getContentSize().height);
	this->addChild(_clip);

	_shadow = Sprite::create();
	Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
	_shadow->setTextureRect(rect);
	_shadow->setPosition(this->getContentSize().width*0.6f, this->getContentSize().height*0.45f);
	_shadow->setColor(Color3B::BLACK);
	_shadow->setOpacity(133);
	_shadow->setZOrder(-1);
	this->addChild(_shadow);

	auto skew = SkewTo::create(3, 3, 0);

	return true;
}

Picture* Picture::create(int id, bool cleared)
{
	Picture *pRet = new Picture();
	if (pRet && pRet->init(id, cleared))
	{
		pRet->autorelease();
		pRet->_stageID = id;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void Picture::setPos(Vec2 pos)
{
	_defaultPos = pos;
}

Vec2 Picture::getPos()
{
	return _defaultPos;
}