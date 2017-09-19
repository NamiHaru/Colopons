#include "TitleScroll.h"
#include "AllTags.h"
#include "TitleBackground.h"

using namespace cocos2d;

bool TitleScroll::init(float scrollSpeed, int clearedStage)
{
	if (!Node::init()) return false;

	float spriteWidthAll = 0.0f;
	int cnt = 0;

	int scrollDir = scrollSpeed / abs(scrollSpeed);

	while (1)
	{
		auto ts = TitleBackground::create(clearedStage);
		/*if (scrollSpeed > 0.0f) */
		ts->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		//else ts->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		this->addChild(ts);

		Size size = ts->getBoundingBox().size;
		ts->setPosition(size.width * cnt * scrollDir, 0.0f);
		_bgSprites.push_back(ts);
		spriteWidthAll += size.width;

		if (spriteWidthAll > designResolutionSize.width + size.width && cnt > 0) break;

		cnt++;
	}
	this->schedule(schedule_selector(ScrollSprite::updateL));

	_scrollSpeed = scrollSpeed;

	return true;
}

TitleScroll* TitleScroll::create(float scrollSpeed, int clearedStage)
{
	TitleScroll* pRet = new TitleScroll();
	if (pRet && pRet->init(scrollSpeed, clearedStage))
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