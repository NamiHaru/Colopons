#include "TitleResetButtonN.h"

using namespace cocos2d;

TitleResetButtonN* TitleResetButtonN::create()
{
	TitleResetButtonN* pRet = new TitleResetButtonN();
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

bool TitleResetButtonN::init()
{
	if (ImageButton::init(false)) return false;

	return true;
}

void TitleResetButtonN::buttonPushed()
{

}