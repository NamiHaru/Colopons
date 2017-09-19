#include "SpriteAnimation.h"

using namespace cocos2d;
using namespace std;

SpriteAnimation* SpriteAnimation::create(string fileName, Size chipSize, float delay)
{
	SpriteAnimation* pRet = new SpriteAnimation();
	if (pRet && pRet->init(fileName, chipSize, delay))
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

bool SpriteAnimation::init(string fileName, Size chipSize, float delay)
{
	if (!Node::init()) return false;

	vector<SpriteFrame*> charSp;	// 切り取ったチップを一時的に格納
	Sprite* sp = Sprite::create(fileName);	// 画像読み込み
	_mySprite = Sprite::create();			// キャラクタースプライト作成
	this->addChild(_mySprite);
	_animationChache = AnimationCache::sharedAnimationCache();		// アニメーションキャッシュに溜めることで読み込み減らす

	int i = 0;
	int width = sp->getContentSize().width / chipSize.width;
	int height = sp->getContentSize().height / chipSize.height;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);
			charSp.push_back(SpriteFrame::createWithTexture(sp->getTexture(), rect));
		}
	}

	// アニメーション作成
	Animation* anim = Animation::create();

	// チップを振り分け
	for (int i = 1; i < width*height; i++)
	{
		anim->addSpriteFrame(charSp[i]);
	}

	// ディレイ設定
	anim->setDelayPerUnit(delay);

	// キャッシュに溜める
	_animationChache->addAnimation(anim, "ANIMATION");

	return true;
}

void SpriteAnimation::startAnimation()
{
	_mySprite->runAction(Animate::create(_animationChache->animationByName("ANIMATION")));
}

void SpriteAnimation::stopAnimation()
{
	_mySprite->stopAllActions();
}