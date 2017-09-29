#include "ResetButton.h"
#include "TitleLayer.h"

using namespace cocos2d;

ResetButton* ResetButton::create(const cocos2d::String path, cocos2d::Color3B color)
{
	ResetButton *pRet = new ResetButton();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		pRet->initWithFile(path.getCString());
		pRet->setColor(color);
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool ResetButton::init()
{
	if (!ImageButton::init(true)) return false;

	return true;
}

void ResetButton::buttonPushed()
{
	((TitleLayer*)this->getParent())->reset();
}