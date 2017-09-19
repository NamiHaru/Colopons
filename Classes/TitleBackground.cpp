#include "TitleBackground.h"
#include "AllTags.h"
#include "TitleTulip.h"
#include "TitleBatterfly.h"
#include "TitleWood.h"

using namespace cocos2d;
using namespace std;

bool TitleBackground::init(int clearedStage)
{
	if (!Sprite::init()) return false;

	auto tulip = TitleTulip::create(clearedStage);
	this->addChild(tulip);

	auto fly = TitleBatterfly::create(clearedStage);
	this->addChild(fly);

	Sprite* ground = Sprite::create("Title/Ground/Brown.png");
	ground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(ground);
	if (clearedStage >= static_cast<int>(eColor::BROWN)) ground->setColor(getColorCode(eColor::BROWN));
	Sprite* green = Sprite::create("Title/Ground/Green.png");
	green->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(green);
	if (clearedStage >= static_cast<int>(eColor::GREEN)) green->setColor(getColorCode(eColor::GREEN));

	this->setContentSize(designResolutionSize * 2.0f);

	return true;
}

TitleBackground* TitleBackground::create(int clearedStage)
{
	TitleBackground* pRet = new TitleBackground();
	if (pRet && pRet->init(clearedStage))
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