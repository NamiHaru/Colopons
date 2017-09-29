#include "MovieBack.h"
#include "AllTags.h"
#include "TitleBackground.h"

using namespace cocos2d;
using namespace std;

bool MovieBack::init()
{
	if (!Node::init()) return false;

	float spriteWidthAll = 0.0f;
	int cnt = 0;
	_scrollSpeed = 3.0f;

	while (1)
	{
		auto ts = TitleBackground::create(9);
		if (_scrollSpeed > 0.0f) ts->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		else ts->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		this->addChild(ts);

		Size size = ts->getBoundingBox().size;
		ts->setPosition(size.width * (cnt - 1), 0.0f);
		_bgSprites.push_back(ts);
		spriteWidthAll += size.width;

		if (spriteWidthAll > designResolutionSize.width + size.width && cnt > 0) break;

		cnt++;
	}
	this->schedule(schedule_selector(ScrollSprite::updateL));

	return true;
}

MovieBack* MovieBack::create()
{
	MovieBack* pRet = new MovieBack();
	if (pRet && pRet->init())
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