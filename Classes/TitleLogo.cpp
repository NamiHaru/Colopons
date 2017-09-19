#include "TitleLogo.h"
#include "AllTags.h"

using namespace cocos2d;

bool TitleLogo::init(Color3B color)
{
	if (!Node::init()) return false;

	_logoSp = Sprite::create("Title/Logos0.png");
	_logoSp->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*1.2f);
	_logoSp->setColor(color);
	auto move = MoveTo::create(3, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.7f));
	_logoSp->runAction(move);
	this->addChild(_logoSp);

	//_shadowSp = Sprite::createWithSpriteFrame(_logoSp->getSpriteFrame());
	_shadowSp = Sprite::create("Title/LogosLight.png");
	//_shadowSp->setColor(Color3B::BLACK);
	//_shadowSp->setOpacity(95);
	//_shadowSp->setScaleY(1.01f);
	//_shadowSp->setScaleX(1.04f);
	_shadowSp->setPosition(_logoSp->getContentSize().width*0.5f, _logoSp->getContentSize().height*0.5f);
	_logoSp->addChild(_shadowSp, -1);

	return true;
}

TitleLogo* TitleLogo::create(Color3B color)
{
	TitleLogo* pRet = new TitleLogo();
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