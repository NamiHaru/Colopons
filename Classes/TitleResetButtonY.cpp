#include "TitleResetButtonY.h"

using namespace cocos2d;

TitleResetButtonY* TitleResetButtonY::create()
{
	TitleResetButtonY* pRet = new TitleResetButtonY();
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

bool TitleResetButtonY::init()
{
	if (ImageButton::init(false)) return false;

	return true;
}

void TitleResetButtonY::buttonPushed()
{

}