#include "Movie.h"
#include "ScrollSprite.h"
#include "AllTags.h"
#include "ColorEnum.h"
#include "TitleWood.h"
#include "Movie2.h"
#include "MovieBase.h"

using namespace cocos2d;

bool Movie::init()
{
	if (!Layer::init()) return false;

	auto sky = Sprite::create();
	Rect rect = Rect(0, 0, designResolutionSize.width, designResolutionSize.height);
	sky->setTextureRect(rect);
	sky->setColor(getColorCode(eColor::SKY));
	sky->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	sky->setPosition(0, 0);
	this->addChild(sky);

	auto wood = TitleWood::create(9);
	this->addChild(wood);

	movieBack = MovieBack::create();
	this->addChild(movieBack);

	auto white = Sprite::create("Movie/White.png");
	white->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	white->setPosition(designResolutionSize.width, 0);

	auto clipping = ClippingNode::create();

	mask = Sprite::create();
	mask->setTextureRect(rect);
	mask->setColor(Color3B::BLACK);
	mask->setAnchorPoint(Vec2(1.2f, 0));
	mask->setPosition(0, 0);
	this->addChild(mask);

	clipping->setStencil(mask);
	clipping->setInverted(false);
	clipping->setAlphaThreshold(0.0f);

	clipping->addChild(white);
	this->addChild(clipping);

	_charAnim = CharacterAnimation::create("Character/TitleAnim_Body.png", "Character/TitleAnim_Head.png", Size(260, 260));
	_charAnim->startAnimation(DIR::RIGHT);
	_charAnim->setPosition(designResolutionSize.width*-0.5f, designResolutionSize.height*0.18f);
	this->addChild(_charAnim);

	float walkTime = 5.2f;
	auto move = MoveTo::create(walkTime, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.18f));

	auto call0 = CallFunc::create([&]() {
		_charAnim->stopAnimation(DIR::RIGHT);
	});
	auto delay0 = DelayTime::create(0.6f);

	auto call1 = CallFunc::create([&]() {
		_charAnim->stopAnimation(DIR::LEFT);
	});
	auto delay1 = DelayTime::create(0.6f);

	auto call2 = CallFunc::create([&]() {
		_charAnim->stopAnimation(DIR::RIGHT);
	});
	auto delay2 = DelayTime::create(1.0f);

	auto call3 = CallFunc::create([&]() {
		_charAnim->stopAnimation(DIR::LEFT);
	});
	auto delay3 = DelayTime::create(1.0f);

	auto call4 = CallFunc::create([&]() {
		_charAnim->startAnimation(DIR::RIGHT);
	});
	auto delay4 = DelayTime::create(1.0f);

	auto move1 = MoveTo::create(2.0f, Vec2(designResolutionSize.width*1.3f, designResolutionSize.height*0.18f));
	auto call = CallFunc::create([&]() {
		auto movie = Movie2::createScene();
		auto tra = TransitionFade::create(2.0f, movie, Color3B::BLACK);
		Director::getInstance()->replaceScene(tra);
	});
	auto seq = Sequence::create(move, call0, delay0, call1, delay1, call2, delay2, call3, delay3, call4, delay4, move1, call, NULL);
	_charAnim->runAction(seq);

	this->scheduleOnce(schedule_selector(Movie::whiting), 3.5f);

	

	return true;
}

void Movie::update(float delta)
{

}

void Movie::whiting(float delta)
{
	Sprite* wind = Sprite::create("Movie/Wind.png");
	wind->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	wind->setPosition(Vec2::ZERO);
	this->addChild(wind);

	float time = 1.5f;
	auto move0 = MoveTo::create(time, Vec2(designResolutionSize.width*1.2f, 0));
	auto move1 = MoveTo::create((time/designResolutionSize.width)*designResolutionSize.width*0.4f, Vec2(designResolutionSize.width*1.4f, 0));
	auto seq = Sequence::create(move0, move1, NULL);

	auto move = MoveTo::create(time, Vec2(designResolutionSize.width * 1.2f, 0));

	wind->runAction(seq);
	mask->runAction(move);
}

Movie* Movie::create()
{
	auto pRet = new Movie();
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

Scene* Movie::createScene()
{
	auto scene = MovieBase::create();
	Movie* movie = Movie::create();
	scene->addChild(movie);
	return scene;
}