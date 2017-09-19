#include "SelectLayer.h"
#include "PictureManager.h"
#include "SelectBackground.h"
#include "AllTags.h"
#include "TitleSelectScene.h"
#include "ColorEnum.h"

using namespace cocos2d;

SelectLayer* SelectLayer::create(SaveData* saveData, cocos2d::Color4F color)
{
	SelectLayer *pRet = new SelectLayer();
	if (pRet && pRet->init(saveData, color))
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

bool SelectLayer::init(SaveData* saveData, Color4F color)
{
	if (!Layer::init())
	{
		return false;
	}

	// ƒQ[ƒ€‚©‚ç‚Ì‘JˆÚ—p

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SelectLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SelectLayer::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Sprite* back = Sprite::create("Select/SelectBackground.png");
	back->setGlobalZOrder(-2);
	back->setPosition(designResolutionSize*0.5f);
	this->addChild(back);

	PictureManager* pictureManager = PictureManager::create(saveData);
	this->addChild(pictureManager);

	_saveData = saveData;

	SelectBackground* selectBackground = SelectBackground::create(Color4F(getColorCode(_saveData->loadLastClear())));
	selectBackground->setZOrder(-1);
	this->addChild(selectBackground);

	auto tapPlease = Sprite::create("Select/TapPlease.png");
	tapPlease->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.9f);
	this->addChild(tapPlease);
	
	Vec2 btnPos = Vec2(designResolutionSize.width*0.07f, designResolutionSize.height*0.9f);
	Color3B btnColor;
	if (!_saveData->loadStarAppear())
		btnColor = getColorCode(static_cast<int>(_saveData->loadTimeZone()));
	else btnColor = getColorCode(eColor::YELLOW);
	_toTitleButton = ToTitleButton::create(btnColor, _saveData->loadLookedSky());
	_toTitleButton->setPosition(btnPos);
	this->addChild(_toTitleButton);

	if (color != Color4F::WHITE)
	{
		// “h‚è‚Â‚Ô‚µ‚½‰~i‘å‚«‚È“_j
		_dot = DrawNode::create();
		_dot->setZOrder(1);
		_dot->drawDot(Vec2::ZERO, designResolutionSize.width * 0.7f, color);
		_dot->setPosition(designResolutionSize*0.5f);
		this->addChild(_dot);

		auto scale = ScaleTo::create(1.0f, 0.0f);
		auto easeIn = EaseSineIn::create(scale);
		auto call = CallFunc::create([&]() {
			_dot->removeFromParentAndCleanup(true);
		});
		auto seq = Sequence::create(easeIn, call, NULL);
		_dot->runAction(seq);
	}

	if (_saveData->loadLookedSky() == false)
	{
		if (static_cast<int>(_saveData->loadTimeZone()) != _saveData->loadLastClear())
		{
			_toTitleButton->startToShine();
			return true;
		}
		float delayTime = 1.0f;
		float moveTime = 1.5f;
		auto particle = ParticleSystemQuad::create("Select/SkyLight.plist");
		if (!_saveData->loadStarAppear())
		{
			particle->setEmissionRate(10.0f);
			particle->setStartColor(Color4F(getColorCode(static_cast<int>(_saveData->loadTimeZone()))));
			particle->setEndColor(Color4F(getColorCode(static_cast<int>(_saveData->loadTimeZone()))));
			particle->setPosition(pictureManager->getPicturePos(static_cast<int>(_saveData->loadTimeZone())));
		}
		else
		{
			particle->setEmissionRate(10.0f);
			particle->setStartColor(Color4F(getColorCode(eColor::YELLOW)));
			particle->setEndColor(Color4F(getColorCode(eColor::YELLOW)));
			particle->setPosition(pictureManager->getPicturePos(static_cast<int>(eColor::YELLOW)));
		}
		particle->setPositionY(particle->getPosition().y - pictureManager->getPictureSize().height*0.5f);
		particle->setDuration(delayTime+moveTime);
		particle->setZOrder(0);
		this->addChild(particle);
		auto delay = DelayTime::create(delayTime);
		auto move = MoveTo::create(moveTime, btnPos);
		auto call = CallFunc::create([&]() {
			_toTitleButton->startToShine();
		});
		auto seq = Sequence::create(delay, move, call, NULL);
		particle->runAction(seq);
	}
	return true;
}

bool SelectLayer::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	Rect rect = _toTitleButton->getBoundingBox();
	if (rect.containsPoint(pTouch->getLocation()))
	{
		return true;
	}
	return false;
}

void SelectLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (_isSceneReplace && ((TitleSelectScene*)this->getParent())->_replaceLayer) return;
	_isSceneReplace = true;

	((TitleSelectScene*)this->getParent())->replaceTitle();
}