#include "EndOpen.h"
#include "AllTags.h"
#include "EndingScene.h"

using namespace cocos2d;

bool EndOpen::init()
{
	if (!Layer::init()) return false;

	auto door = Sprite::create("Ending/Door.png");
	door->setPosition(designResolutionSize*0.5f);
	this->addChild(door);	

	_leftWall = Sprite::create("Ending/WallLeft.png");
	_leftWall->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	_leftWall->setPosition(designResolutionSize*0.5f);
	this->addChild(_leftWall);

	_rightWall = Sprite::create("Ending/WallRight.png");
	_rightWall->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_rightWall->setPosition(designResolutionSize*0.5f);
	this->addChild(_rightWall);

	auto hashira = Sprite::create("Ending/Hashira.png");
	hashira->setPosition(designResolutionSize*0.5f);
	this->addChild(hashira);

	auto body = Sprite::create("Character/EndingAnim_Body.png");
	auto head = Sprite::create("Character/EndingAnim_Head.png");

	Rect puriketsu = Rect(0, 510, 510, 510);
	Vec2 colo0Pos = Vec2(designResolutionSize.width*0.6f, designResolutionSize.height*0.17f);
	Vec2 colo1Pos = Vec2(designResolutionSize.width*0.4f, designResolutionSize.height*0.17f);

	auto colo0B = Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(body->getTexture(), puriketsu));
	colo0B->setPosition(colo0Pos);
	this->addChild(colo0B);
	auto colo0H = Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(head->getTexture(), puriketsu));
	colo0H->setPosition(colo0Pos);
	this->addChild(colo0H);

	auto colo1B = Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(body->getTexture(), puriketsu));
	colo1B->setPosition(colo1Pos);
	this->addChild(colo1B);
	auto colo1H = Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(head->getTexture(), puriketsu));
	colo1H->setPosition(colo1Pos);
	this->addChild(colo1H);

	float time = 0.8f;
	auto delayBR = DelayTime::create(time);
	auto flipBR = FlipX::create(true);
	auto delayBL = DelayTime::create(time);
	auto flipBL = FlipX::create(false);
	auto seqB = Sequence::create(delayBR, flipBR, delayBL, flipBL, NULL);
	auto repB = RepeatForever::create(seqB);
	auto delayHR = DelayTime::create(time);
	auto flipHR = FlipX::create(true);
	auto delayHL = DelayTime::create(time);
	auto flipHL = FlipX::create(false);
	auto seqH = Sequence::create(delayHR, flipHR, delayHL, flipHL, NULL);
	auto repH = RepeatForever::create(seqH);
	colo0B->runAction(repB);
	colo0H->runAction(repH);

	float fadeStartTime = 2.5f;
	auto delay1H = DelayTime::create(fadeStartTime);
	auto fade1H = FadeOut::create(3.0f);
	auto seq1H = Sequence::create(delay1H, fade1H, NULL);
	auto delay1B = DelayTime::create(fadeStartTime);
	auto fade1B = FadeOut::create(3.0f);
	auto seq1B = Sequence::create(delay1B, fade1B, NULL);
	colo1H->runAction(seq1H);
	colo1B->runAction(seq1B);

	// •Ç@ˆÚ“®
	auto delayL = DelayTime::create(2.0f);
	auto delayR = DelayTime::create(2.0f);
	auto moveL = MoveTo::create(7.0f, Vec2(0, designResolutionSize.height*0.5f));
	auto easeL = EaseIn::create(moveL, 2.0f);
	auto moveR = MoveTo::create(7.0f, Vec2(designResolutionSize.width, designResolutionSize.height*0.5f));
	auto easeR = EaseIn::create(moveR, 2.0f);
	auto seqL = Sequence::create(delayL, easeL, NULL);
	auto seqR = Sequence::create(delayR, easeR, NULL);

	_leftWall->runAction(seqL);
	_rightWall->runAction(seqR);

	/*_light = DrawNode::create();
	_light->drawDot(Vec2::ZERO, 20.0f, Color4F::WHITE);*/
	_light = Sprite::create("Ending/Light.png");
	_light->setPosition(designResolutionSize*0.5f);
	_light->setScale(0.0f);
	_light->setZOrder(-1);
	this->addChild(_light);

	auto delay = DelayTime::create(3.0f);
	auto call = CallFunc::create([&]() {
		_light->setZOrder(1);
	});
	auto scale = ScaleTo::create(2.0f, 2.0f);
	auto ease = EaseIn::create(scale, 3.0f);
	auto end = CallFunc::create([&]() {
		((EndingScene*)this->getParent())->replace(this);
	});
	auto seq = Sequence::create(delay, call, ease, end, NULL);
	_light->runAction(seq);

	return true;
}