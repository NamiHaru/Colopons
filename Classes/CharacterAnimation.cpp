#include "CharacterAnimation.h"
#include <cmath>

using namespace cocos2d;
using namespace std;

bool CharacterAnimation::init(string fileName, string ponFileName, Size chipSize, float delay, bool move)
{
	if (!Node::init()) return false;

	size = chipSize;
	vector<SpriteFrame*> charSp;	// 切り取ったチップを一時的に格納
	vector<SpriteFrame*> ponSp;		// 切り取ったチップをポンに格納
	Sprite* sp = Sprite::create(fileName);	// 画像読み込み
	Sprite* pn = Sprite::create(ponFileName);	// ポン読み込み
	_mySprite = Sprite::create();			// キャラクタースプライト作成
	_ponSprite = Sprite::create();		// ポンスプライト作成
	this->addChild(_mySprite);
	this->addChild(_ponSprite);
	
	_animationChache = AnimationCache::sharedAnimationCache();		// アニメーションキャッシュに溜めることで読み込み減らす

	int i = 0;
	int width = sp->getContentSize().width / chipSize.width;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);
			charSp.push_back(SpriteFrame::createWithTexture(sp->getTexture(), rect));
			ponSp.push_back(SpriteFrame::createWithTexture(pn->getTexture(), rect));
		}
	}

	//-----------------------------------------------------------------------------------------
	// 移動用アニメーション
	//-----------------------------------------------------------------------------------------
	// アニメーション作成
	Animation* _animFront = Animation::create();
	Animation* _animBack = Animation::create();
	Animation* _animLeft = Animation::create();
	Animation* _animRight = Animation::create();

	Animation* _ponFront = Animation::create();
	Animation* _ponBack = Animation::create();
	Animation* _ponLeft = Animation::create();
	Animation* _ponRight = Animation::create();

	// チップを振り分け
	for (int i = 1; i < width; i++)
	{
		_animFront->addSpriteFrame(charSp[i]);
		_animBack->addSpriteFrame(charSp[width + i]);
		_animLeft->addSpriteFrame(charSp[2 * width + i]);
		_animRight->addSpriteFrame(charSp[3 * width + i]);

		_ponFront->addSpriteFrame(ponSp[i]);
		_ponBack->addSpriteFrame(ponSp[width + i]);
		_ponLeft->addSpriteFrame(ponSp[2 * width + i]);
		_ponRight->addSpriteFrame(ponSp[3 * width + i]);
	}

	// ディレイ設定
	_animFront->setDelayPerUnit(delay);
	_animBack->setDelayPerUnit(delay);
	_animLeft->setDelayPerUnit(delay);
	_animRight->setDelayPerUnit(delay);

	_ponFront->setDelayPerUnit(delay);
	_ponBack->setDelayPerUnit(delay);
	_ponLeft->setDelayPerUnit(delay);
	_ponRight->setDelayPerUnit(delay);

	// キャッシュに溜める
	_animationChache->addAnimation(_animFront, "FRONT");
	_animationChache->addAnimation(_animBack, "BACK");
	_animationChache->addAnimation(_animLeft, "LEFT");
	_animationChache->addAnimation(_animRight, "RIGHT");

	_animationChache->addAnimation(_ponFront, "P_FRONT");
	_animationChache->addAnimation(_ponBack, "P_BACK");
	_animationChache->addAnimation(_ponLeft, "P_LEFT");
	_animationChache->addAnimation(_ponRight, "P_RIGHT");

	//-----------------------------------------------------------------------------------------
	// ストップ用アニメーション
	//-----------------------------------------------------------------------------------------
	// アニメーション作成
	Animation* _stopFront = Animation::create();
	Animation* _stopBack = Animation::create();
	Animation* _stopLeft = Animation::create();
	Animation* _stopRight = Animation::create();

	Animation* _ponStopFront = Animation::create();
	Animation* _ponStopBack = Animation::create();
	Animation* _ponStopLeft = Animation::create();
	Animation* _ponStopRight = Animation::create();

	// チップ振り分け
	_stopFront->addSpriteFrame(charSp[0]);
	_stopBack->addSpriteFrame(charSp[width]);
	_stopLeft->addSpriteFrame(charSp[width*2]);
	_stopRight->addSpriteFrame(charSp[width*3]);

	_ponStopFront->addSpriteFrame(ponSp[0]);
	_ponStopBack->addSpriteFrame(ponSp[width]);
	_ponStopLeft->addSpriteFrame(ponSp[width * 2]);
	_ponStopRight->addSpriteFrame(ponSp[width * 3]);

	// ディレイ設定
	_stopFront->setDelayPerUnit(delay);
	_stopBack->setDelayPerUnit(delay);
	_stopLeft->setDelayPerUnit(delay);
	_stopRight->setDelayPerUnit(delay);

	_ponStopFront->setDelayPerUnit(delay);
	_ponStopBack->setDelayPerUnit(delay);
	_ponStopLeft->setDelayPerUnit(delay);
	_ponStopRight->setDelayPerUnit(delay);

	// キャッシュに溜める
	_animationChache->addAnimation(_stopFront, "STOP_F");
	_animationChache->addAnimation(_stopBack, "STOP_B");
	_animationChache->addAnimation(_stopLeft, "STOP_L");
	_animationChache->addAnimation(_stopRight, "STOP_R");

	_animationChache->addAnimation(_ponStopFront, "P_STOP_F");
	_animationChache->addAnimation(_ponStopBack, "P_STOP_B");
	_animationChache->addAnimation(_ponStopLeft, "P_STOP_L");
	_animationChache->addAnimation(_ponStopRight, "P_STOP_R");

	_dir = eDIR::FRONT;
	_movedAnim = move;
	_movedAnim = !_movedAnim;
	if (!_movedAnim) startAnimation();
	else stopAnimation();

	return true;
}

CharacterAnimation* CharacterAnimation::create(string fileName, string ponFileName, Size chipSize, float delay)
{
	CharacterAnimation* pRet = new CharacterAnimation();
	if (pRet && pRet->init(fileName, ponFileName, chipSize, delay, true))
	{
		pRet->autorelease();
		pRet->_movedAnim = true;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

CharacterAnimation* CharacterAnimation::createInStop(string fileName, string ponFileName, Size chipSize, float delay)
{
	CharacterAnimation* pRet = new CharacterAnimation();
	if (pRet && pRet->init(fileName, ponFileName, chipSize, delay, false))
	{
		pRet->autorelease();
		pRet->_movedAnim = false;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

CharacterAnimation* CharacterAnimation::createInMove(string fileName, string ponFileName, Size chipSize, float delay)
{
	CharacterAnimation* pRet = new CharacterAnimation();
	if (pRet && pRet->init(fileName, ponFileName, chipSize, delay, true))
	{
		pRet->autorelease();
		pRet->_movedAnim = true;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void CharacterAnimation::changeAnimation(eDIR dirName)
{
	if (_movedAnim)
	{
		startAnimation(dirName);
	}
	else
	{
		stopAnimation(dirName);
	}
}

void CharacterAnimation::changeAnimation(Vec2 dir)
{
	if (abs(dir.x) > abs(dir.y))
	{
		if (dir.x > 0.0f)
		{
			// 右
			changeAnimation(eDIR::RIGHT);
		}
		else
		{
			// 左
			changeAnimation(eDIR::LEFT);
		}
	}
	else
	{
		if (dir.y > 0.0f)
		{
			// 後ろ
			changeAnimation(eDIR::BACK);
		}
		else
		{
			// 前
			changeAnimation(eDIR::FRONT);
		}
	}
}

void CharacterAnimation::startAnimation(eDIR dirName)
{
	if (_movedAnim && _dir == dirName) return;
	_mySprite->stopAllActions();
	_ponSprite->stopAllActions();
	_dir = dirName;
	_movedAnim = true;
	Animation* anim;
	Animation* ponA;
	switch (dirName)
	{
	case eDIR::FRONT:
		anim = _animationChache->animationByName("FRONT");
		ponA = _animationChache->animationByName("P_FRONT");
		break;
	case eDIR::BACK:
		anim = _animationChache->animationByName("BACK");
		ponA = _animationChache->animationByName("P_BACK");
		break;
	case eDIR::LEFT:
		anim = _animationChache->animationByName("LEFT");
		ponA = _animationChache->animationByName("P_LEFT");
		break;
	case eDIR::RIGHT:
		anim = _animationChache->animationByName("RIGHT");
		ponA = _animationChache->animationByName("P_RIGHT");
		break;
	default:
		break;
	}
	auto action = RepeatForever::create(Animate::create(anim));
	auto pAction = RepeatForever::create(Animate::create(ponA));
	_mySprite->runAction(action);
	_ponSprite->runAction(pAction);
}

void CharacterAnimation::startAnimation()
{
	if (_movedAnim) return;
	startAnimation(_dir);
}

void CharacterAnimation::stopAnimation(eDIR dirName)
{
	if (_movedAnim == false && _dir == dirName) return;
	_mySprite->stopAllActions();
	//_ponSprite->stopAllActions();
	_dir = dirName;
	_movedAnim = false;
	Animation* anim;
	//Animation* ponA;
	switch (dirName)
	{
	case eDIR::FRONT:
		anim = _animationChache->animationByName("STOP_F");
		//ponA = _animationChache->animationByName("P_STOP_F");
		break;
	case eDIR::BACK:
		anim = _animationChache->animationByName("STOP_B");
		//ponA = _animationChache->animationByName("P_STOP_B");
		break;
	case eDIR::LEFT:
		anim = _animationChache->animationByName("STOP_L");
		//ponA = _animationChache->animationByName("P_STOP_L");
		break;
	case eDIR::RIGHT:
		anim = _animationChache->animationByName("STOP_R");
		//ponA = _animationChache->animationByName("P_STOP_R");
		break;
	default:
		break;
	}
	auto action = RepeatForever::create(Animate::create(anim));
	//auto pAction = RepeatForever::create(Animate::create(ponA));
	_mySprite->runAction(action);
	//_ponSprite->runAction(pAction);
}

void CharacterAnimation::stopAnimation()
{
	if (!_movedAnim) return;
	stopAnimation(_dir);
}

void CharacterAnimation::stopPonAnim(eDIR dirName)
{
	_ponSprite->stopAllActions();
	Animation* ponA;
	switch (dirName)
	{
	case CharacterAnimation::eDIR::FRONT:
		ponA = _animationChache->animationByName("P_STOP_F");
		break;
	case CharacterAnimation::eDIR::BACK:
		ponA = _animationChache->animationByName("P_STOP_B");
		break;
	case CharacterAnimation::eDIR::LEFT:
		ponA = _animationChache->animationByName("P_STOP_L");
		break;
	case CharacterAnimation::eDIR::RIGHT:
		ponA = _animationChache->animationByName("P_STOP_R");
		break;
	default:
		break;
	}
	auto pAction = RepeatForever::create(Animate::create(ponA));
	_ponSprite->runAction(pAction);
}

void CharacterAnimation::stopPonAnim()
{
	stopPonAnim(_dir);
}

void CharacterAnimation::stopAction()
{
	_mySprite->stopAllActions();
	_ponSprite->stopAllActions();
}

Sprite* CharacterAnimation::getSp()
{
	return _mySprite;
}

void CharacterAnimation::setDelay(float delayTime)
{
	_animationChache->animationByName("FRONT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("BACK")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("RIGHT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("LEFT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_F")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_B")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_R")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_L")->setDelayPerUnit(delayTime);

	_animationChache->animationByName("P_FRONT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_BACK")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_RIGHT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_LEFT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_STOP_F")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_STOP_B")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_STOP_R")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_STOP_L")->setDelayPerUnit(delayTime);
}

float CharacterAnimation::getDelay()
{
	return _animationChache->animationByName("FRONT")->getDelayPerUnit();
}

void CharacterAnimation::setDir(Vec2 dir)
{
	changeAnimation(dir);
}

void CharacterAnimation::setDir(eDIR dirName)
{
	changeAnimation(dirName);
}

Sprite* CharacterAnimation::getPon()
{
	return _ponSprite;
}

Size CharacterAnimation::getSpriteSize()
{
	return size;
}

void CharacterAnimation::setFlipX(bool is)
{
	if (_isFliped == is) return;
	this->setRotation3D(Vec3(0, 180, 0));
}

void CharacterAnimation::setFlipY(bool is)
{
	if (_isFliped == is) return;
	this->setRotation3D(Vec3(180, 0, 0));
}