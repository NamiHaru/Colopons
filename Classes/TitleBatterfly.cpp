#include "TitleBatterfly.h"
#include "AllTags.h"

using namespace cocos2d;

bool TitleBatterfly::init(int clearedStage)
{
	if (!Node::init()) return false;

	for (int i = 0; i < 2; i++)
	{
		_batterfly[i] = Batterfly::create();
		this->addChild(_batterfly[i]);
	}
	_batterfly[0]->setPosition(designResolutionSize*0.5f);
	_batterfly[1]->setPosition(designResolutionSize.width*0.35f, designResolutionSize.height*0.55f);
	_batterfly[1]->setScale(0.6f);
	_batterfly[1]->setFlipX(true);

	if (clearedStage >= static_cast<int>(eColor::BLUE))
	{
		_batterfly[0]->setColor(getColorCode(eColor::BLUE));
	}
	if (clearedStage >= static_cast<int>(eColor::PURPLE))
	{
		_batterfly[1]->setColor(getColorCode(eColor::PURPLE));
	}

	return true;
}

TitleBatterfly* TitleBatterfly::create(int clearedStage)
{
	auto pRet = new TitleBatterfly();
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