#include "Movie2.h"
#include "AllTags.h"
#include "ColorEnum.h"
#include "Movie3.h"
#include "MovieBase.h"
//#include "SaveData.h"

using namespace cocos2d;

bool Movie2::init()
{
	if (!Layer::init()) return false;

	//SaveData* save = SaveData::create();
	//save->AllResset();

	auto entrance = Sprite::create("Movie/Entrance.png");
	entrance->setPosition(designResolutionSize*0.5f);
	this->addChild(entrance);

	_charAnim = CharacterAnimation::create("Character/TitleAnim_Body.png", "Character/TitleAnim_Head.png", Size(260, 260));
	_charAnim->stopAllAnimation(DIR::BACK);
	_charAnim->setScale(3.0f);
	_charAnim->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.18f);
	this->addChild(_charAnim);

	auto delay = DelayTime::create(5.0f);
	auto call = CallFunc::create([&]() {
		_charAnim->startAnimation(DIR::BACK);
	});
	auto scale = ScaleTo::create(5.0f, 1.0f);
	auto move1 = MoveTo::create(5.0f, Vec2(designResolutionSize.width * 0.5f, designResolutionSize.height * 0.05f));
	auto spa = Spawn::create(scale, move1, NULL);
	auto call0 = CallFunc::create([&]() {
		auto scene = Movie3::createScene();
		auto transition = TransitionFade::create(2.0f, scene);
		Director::getInstance()->replaceScene(transition);
	});
	auto seq = Sequence::create(delay, call, spa, call0, NULL);
	_charAnim->runAction(seq);

	return true;
}

void Movie2::update(float delta)
{

}

Movie2* Movie2::create()
{
	auto pRet = new Movie2();
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

Scene* Movie2::createScene()
{
	auto scene = MovieBase::create();
	Movie2* movie2 = Movie2::create();
	scene->addChild(movie2);
	return scene;
}