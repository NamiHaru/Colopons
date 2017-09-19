#include "SelectBackground.h"
#include "AllTags.h"

using namespace cocos2d;

SelectBackground* SelectBackground::create(Color4F color)
{
	SelectBackground* pRet = new SelectBackground();
	if (pRet && pRet->init(color))
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

bool SelectBackground::init(Color4F color)
{
	if (!Node::init()) return false;

	int sizeX = 0, sizeY = 0;
	float sumX = 0.0f, sumY = 0.0f;
	ParticleSystemQuad* p = ParticleSystemQuad::create("Select/SelectBack.plist");
	p->setPosition(designResolutionSize*0.5f);
	p->setPosVar(designResolutionSize*0.5f);
	p->setStartColor(Color4F(color.r,color.g,color.b,1));
	p->setEndColor(Color4F(color.r, color.g, color.b, 0.5f));
	p->setStartSpin(0.0f);
	p->setStartSpinVar(0.0f);
	p->setEndSizeVar(0.0f);
	p->setEmissionRate(0.00010417 * (designResolutionSize.width*designResolutionSize.height));
	this->addChild(p);

	return true;
}