#include "TitleWood.h"
#include "AllTags.h"
#include "ColorEnum.h"
#include <vector>

using namespace cocos2d;
using namespace std;

bool TitleWood::init(int clearedStage)
{
	if (!Node::init()) return false;

	vector<SpriteFrame*> charSp;	// Ø‚èŽæ‚Á‚½ƒ`ƒbƒv‚ðˆêŽž“I‚ÉŠi”[
	Sprite* gr = Sprite::create("Title/Wood/Green.png");	// ‰æ‘œ“Ç‚Ýž‚Ý
	Sprite* br = Sprite::create("Title/Wood/Brown.png");	// ‰æ‘œ“Ç‚Ýž‚Ý

	int i = 0;
	Size chipSize = Size(900, 1035);
	int width = gr->getContentSize().width / chipSize.width;
	int height = gr->getContentSize().height / chipSize.height;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);

			_wood[i] = Wood::create(SpriteFrame::createWithTexture(gr->getTexture(), rect),
				SpriteFrame::createWithTexture(br->getTexture(), rect), clearedStage);

			_wood[i]->setPosition(Vec2((designResolutionSize.width*2) / 4 * i, designResolutionSize.height*0.08f));
			this->addChild(_wood[i]);

			i++;
		}
	}

	this->setContentSize(designResolutionSize*2.0f);

	return true;
}

TitleWood* TitleWood::create(int clearedStage)
{
	auto pRet = new TitleWood();
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