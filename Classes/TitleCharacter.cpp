#include "TitleCharacter.h"
#include "TitleLayer.h"

using namespace cocos2d;

bool TitleCharacter::init()
{
	if (!Sprite::init()) return false;

	_charAnim = CharacterAnimation::create("Character/TitleAnim_Body.png", "Character/TitleAnim_Head.png", Size(260, 260), _walkTime);
	this->addChild(_charAnim);
	_charAnim->changeAnimation(DIR::RIGHT);
	_state = eSTATE::MOVE;

	this->scheduleUpdate();

	return true;
}

TitleCharacter* TitleCharacter::create()
{
	TitleCharacter* pRet = new TitleCharacter();
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

void TitleCharacter::update(float delta)
{
	switch (_state)
	{
	case TitleCharacter::MOVE:
		if (_timer > 5.0f)
		{
			_state = eSTATE::STAND;
			_timer = 0.0f;
			_charAnim->stopAnimation(DIR::FRONT);
			_charAnim->stopPonAnim(DIR::FRONT);
			changeState();
			((TitleLayer*)this->getParent())->setScrollStop();
		}
		break;
	case TitleCharacter::STAND:
		if (_timer > 2.0f)
		{
			_state = eSTATE::JUMP;
			_timer = 0.0f;
			_charAnim->setDelay(0.5f);
			_charAnim->startAnimation(DIR::FRONT);
			auto rotateR = RotateTo::create(0.5f,15);
			auto rotateL = RotateTo::create(0.5f, -15);
			auto rotateC = RotateTo::create(0.5f, 3);
			auto jump = JumpBy::create(0.5f, Vec2(0, 0), 20.0f, 1);
			auto flip = FlipX::create(true);
			auto flipF = FlipX::create(false);
			auto spo0 = Spawn::create(jump, rotateR, NULL);
			auto spo1 = Spawn::create(jump, rotateL, NULL);
			auto spo2 = Spawn::create(jump, rotateC, NULL);
			auto call = CallFunc::create([&]() {_charAnim->stopAction(); });
			auto seq = Sequence::create(spo0, spo1, spo0, spo2, call, NULL);
			_charAnim->runAction(seq);
		}
		break;
	case TitleCharacter::JUMP:
		if (_timer > 3.0f)
		{
			_state = eSTATE::MOVE;
			_charAnim->setRotation(0);
			_charAnim->setDelay(_walkTime);
			_timer = 0.0f;
			_charAnim->startAnimation(DIR::RIGHT);
			((TitleLayer*)this->getParent())->setDefaultSpeed();
			changeState();
		}
		break;
	default:
		break;
	}
	_timer += delta;
}

void TitleCharacter::changeState()
{
	auto jump = JumpBy::create(0.5f, Vec2(0, 0), 5.0f, 1);
	_charAnim->runAction(jump);
}

void TitleCharacter::setColor(Color3B color)
{
	_charAnim->getPon()->setColor(color);
}