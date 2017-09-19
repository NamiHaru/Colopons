#include "TitleLayer.h"
#include "TitleCharacter.h"
#include "TitleLogo.h"
#include "TitleSelectScene.h"
#include "ColorEnum.h"

using namespace cocos2d;

bool TitleLayer::init(SaveData* saveData)
{
	if (!Layer::init()) return false;

	_replacedScene = false;

	// DEBUG
	//saveData->user->setIntegerForKey("clear", 8);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TitleLayer::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	_saveData = saveData;
	_saveData->saveLookedSky(true);

	Rect rect = Rect(0, 0, designResolutionSize.width, designResolutionSize.height);
	Sprite* sky = Sprite::create();
	sky->setTextureRect(rect);
	sky->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(sky);
	
	ScrollSprite* deco;
	float decoSpeed = 0.05f;
	switch (_saveData->loadTimeZone())
	{
	case MORNING:
		sky->setColor(getColorCode(eColor::SKY));

		decoSpeed = 0.5f;
		deco = ScrollSprite::create("Title/Cloud.png", decoSpeed, ScrollSprite::eOrientation::landscape);
		this->addChild(deco);		
		break;
	case EVENING:
		sky->setColor(getColorCode(eColor::ORANGE));

		if (_saveData->loadStarAppear())
		{
			deco = ScrollSprite::create("Title/OneStar.png", decoSpeed, ScrollSprite::eOrientation::landscape, getColorCode(eColor::YELLOW));
			this->addChild(deco);
		}		
		break;
	case NIGHT:
		sky->setColor(getColorCode(eColor::INDIGO));

		if (_saveData->loadStarAppear())
		{
			deco = ScrollSprite::create("Title/Star.png", decoSpeed, ScrollSprite::eOrientation::landscape, getColorCode(eColor::YELLOW));
			this->addChild(deco);
		}		
		break;
	default:
		break;
	}
	
	int cleareStage = _saveData->loadClear();

	ws = WoodScroll::create(_woodScrollSpeed, cleareStage);
	this->addChild(ws);

	ts = TitleScroll::create(_scrollSpeed, cleareStage);
	this->addChild(ts);

	TitleCharacter* titleCharacter = TitleCharacter::create();
	titleCharacter->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.18f);
	if (_saveData->loadClear() >= 0) titleCharacter->setColor(getColorCode(_saveData->loadLastClear()));
	this->addChild(titleCharacter);

	TitleLogo* titleLogo;
	if (_saveData->loadClear() >= 0) titleLogo = TitleLogo::create(getColorCode(_saveData->loadLastClear()));
	else titleLogo = TitleLogo::create();
	this->addChild(titleLogo);

	return true;
}

TitleLayer* TitleLayer::create(SaveData* saveData)
{
	TitleLayer* pRet = new TitleLayer();
	if (pRet && pRet->init(saveData))
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

bool TitleLayer::onTouchBegan(Touch* touch, Event* event)
{
	float base = 50.0f;
	// リセット機能
	
	/*auto str = String::createWithFormat("%f, %f", touch->getLocation().x, touch->getLocation().y);
	label->setString(str->getCString());*/
	
	if (touch->getLocation().x < base && touch->getLocation().y > designResolutionSize.height - base)
	{
		_saveData->AllResset();
		auto scene = TitleSelectScene::createTitleScene();
		auto transition = TransitionPageTurn::create(0.5f, scene, 1);
		Director::getInstance()->replaceScene(transition);
	}

	if (_replacedScene && ((TitleSelectScene*)this->getParent())->_replaceLayer) return false;
	_replacedScene = true;
	((TitleSelectScene*)this->getParent())->replaceSelect();
	return true;
}

void TitleLayer::setScrollStop()
{
	ws->setScrollSpriteSpeed(0);
	ts->setScrollSpriteSpeed(0);
}

void TitleLayer::setDefaultSpeed()
{
	ws->setScrollSpriteSpeed(_woodScrollSpeed);
	ts->setScrollSpriteSpeed(_scrollSpeed);
}