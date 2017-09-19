#include "Wood.h"

using namespace cocos2d;

bool Wood::init(SpriteFrame* gr, SpriteFrame* br, int clearedStage)
{
	if (!Sprite::init()) return false;

	// 茶
	_br = Sprite::create();		// キャラクタースプライト作成
	_br->setSpriteFrame(br);
	_br->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->addChild(_br);
	if (clearedStage >= static_cast<int>(eColor::BROWN)) _br->setColor(getColorCode(eColor::BROWN));
	// 緑
	_gr = Sprite::create();		// キャラクタースプライト作成
	_gr->setSpriteFrame(gr);
	_gr->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->addChild(_gr);
	if (clearedStage >= static_cast<int>(eColor::GREEN)) _gr->setColor(getColorCode(eColor::GREEN));

	//// 黒ライン
	//_bl = Sprite::create();		// キャラクタースプライト作成
	//_bl->setSpriteFrame(bl);
	//_bl->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	//this->addChild(_bl);

	return true;
}

Wood* Wood::create(SpriteFrame* gr, SpriteFrame* br, int clearedStage)
{
	auto pRet = new Wood();
	if (pRet && pRet->init(gr, br, clearedStage))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return pRet;
	}
}