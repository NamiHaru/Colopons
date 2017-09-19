#include "EndStart.h"
#include "AllTags.h"
#include "ColorEnum.h"
#include <vector>
#include "ScrollSprite.h"
#include "EndingScene.h"

using namespace cocos2d;
using namespace std;

bool EndStart::init()
{
	if (!Layer::init()) return false;

	auto rect /*= Rect(0, 0, designResolutionSize.width, designResolutionSize.height*0.5f);

	rect*/ = Rect(0, 0, designResolutionSize.width, designResolutionSize.height);
	auto back = Sprite::create();
	back->setTextureRect(rect);
	back->setColor(getColorCode(eColor::GREEN));
	back->setPosition(designResolutionSize*0.5f);
	this->addChild(back);

	auto shadow = Sprite::create("Character/Shadow.png");
	for (int i = 0; i < 6; i++)
	{
		_chara[i] = EndingCharacterAnimation::createInStand("Character/EndingAnim_Body2.png", "Character/EndingAnim_Head2.png", "Character/EndingAnim_Face2.png", Size(510, 510), 0.5f);
		this->addChild(_chara[i]);
		_chara[i]->setShadow(shadow->getSpriteFrame());
	}

	vector<SpriteFrame*> charSp;	// Ø‚èŽæ‚Á‚½ƒ`ƒbƒv‚ðˆêŽž“I‚ÉŠi”[
	Sprite* gr = Sprite::create("Title/Wood/Green.png");	// ‰æ‘œ“Ç‚Ýž‚Ý
	Sprite* br = Sprite::create("Title/Wood/Brown.png");	// ‰æ‘œ“Ç‚Ýž‚Ý
	Sprite* sh = Sprite::create("Ending/WoodShadow.png");	// ‰æ‘œ“Ç‚Ýž‚Ý

	int i = 0;
	Size chipSize = Size(900, 1035);
	int width = gr->getContentSize().width / chipSize.width;
	int height = gr->getContentSize().height / chipSize.height;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);

			_woodShadow[i] = Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(sh->getTexture(), rect));
			this->addChild(_woodShadow[i]);
			_wood[i] = Wood::create(SpriteFrame::createWithTexture(gr->getTexture(), rect),
				SpriteFrame::createWithTexture(br->getTexture(), rect), 9);
			this->addChild(_wood[i]);

			_woodShadow[i + 4] = Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(sh->getTexture(), rect));
			_woodShadow[i + 4]->setZOrder(1);
			this->addChild(_woodShadow[i + 4]);
			_wood[i + 4] = Wood::create(SpriteFrame::createWithTexture(gr->getTexture(), rect),
				SpriteFrame::createWithTexture(br->getTexture(), rect), 9);
			_wood[i + 4]->setZOrder(1);
			this->addChild(_wood[i + 4]);
			i++;
		}
	}


	_wood[7]->setScale(1.6f);
	_wood[7]->setPosition(designResolutionSize.width*0.18f, designResolutionSize.height*0.0f);
	_wood[6]->setScale(1.4f);
	_wood[6]->setPosition(designResolutionSize.width*0.82f, designResolutionSize.height*0.03f);
	_wood[5]->setScale(1.3f);
	_wood[5]->setPosition(designResolutionSize.width*0.4f, designResolutionSize.height*0.1f);
	_wood[4]->setScale(1.0f);
	_wood[4]->setPosition(designResolutionSize.width*0.98f, designResolutionSize.height*0.25f);
	_wood[3]->setScale(0.8f);
	_wood[3]->setPosition(designResolutionSize.width*0.65f, designResolutionSize.height*0.26f);
	_wood[2]->setScale(0.7f);
	_wood[2]->setPosition(designResolutionSize.width*0.0f, designResolutionSize.height*0.33f);
	_wood[1]->setScale(0.5f);
	_wood[1]->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.4f);
	_wood[0]->setScale(0.3f);
	_wood[0]->setPosition(designResolutionSize.width*0.23f, designResolutionSize.height*0.4f);

	float cSize = _chara[5]->getSpriteSize().width*0.5f;

	_chara[5]->setScale(1.1f * 0.5f);
	_chara[5]->setPosition(_wood[7]->getPositionX() + cSize * 0.4f, _wood[7]->getPositionY() + cSize * 0.65f);
	_chara[4]->setPosition(_wood[6]->getPositionX() - cSize * 0.25f, _wood[6]->getPositionY() + cSize * 0.63f);
	_chara[4]->setScale(0.5f);
	_chara[3]->setFlipX(true);
	_chara[3]->setScale(0.5f);
	_chara[3]->setPosition(_wood[6]->getPositionX() + cSize * 0.65f, _wood[6]->getPositionY() + cSize * 0.63f);
	_chara[2]->setScale(0.9f * 0.5f);
	_chara[2]->setFlipX(true);
	_chara[2]->setPosition(_wood[5]->getPositionX() - cSize * 0.2f, _wood[5]->getPositionY() + cSize * 0.6f);
	_chara[1]->setScale(0.75f * 0.5f);
	_chara[1]->setFlipX(true);
	_chara[1]->setPosition(_wood[3]->getPositionX() - cSize * 0.23f, _wood[3]->getPositionY() + cSize * 0.4f);
	_chara[0]->setScale(0.63f * 0.5f);
	_chara[0]->setPosition(_wood[2]->getPositionX() + cSize * 0.3f, _wood[2]->getPositionY() + cSize * 0.35f);

	for (int i = 0; i < 8; i++)
	{
		_woodShadow[i]->setPosition(_wood[i]->getPosition() + Vec2(10, 0));
		_woodShadow[i]->setScale(_wood[i]->getScale());
		_woodShadow[i]->setOpacity(125);
		_woodShadow[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	}

	auto delay1 = DelayTime::create(2.0f);
	auto call0 = CallFunc::create([&]() {
		_chara[5]->changeDir(eDIR::RIGHT);
		_chara[5]->changeAnimation(eENDSTATE::WALK);
		
	});
	auto move0 = MoveBy::create(2.0f, Vec2(110.0f, 0.0f));
	auto call1 = CallFunc::create([&]() {
		_chara[5]->changeDir(eDIR::FRONT);
		_chara[5]->changeAnimation(eENDSTATE::STAND);
	});
	auto delay0 = DelayTime::create(2.0f);
	auto call2 = CallFunc::create([&]() {
		_chara[5]->changeAnimation(eENDSTATE::WALK);
		_chara[5]->setZOrder(2);
	});

	auto move1 = MoveTo::create(7.0f, Vec2(designResolutionSize.width * 0.5f, designResolutionSize.height*0.65));
	auto scale0 = ScaleTo::create(7.0f, 4.0f);
	auto spawn0 = Spawn::create(move1, scale0, NULL);
	auto ease0 = EaseIn::create(spawn0, 2.0f);

	auto call3 = CallFunc::create([&]() {
		_chara[5]->changeAnimation(eENDSTATE::STAND);
	});
	auto delay2 = DelayTime::create(1.0f);
	auto call4 = CallFunc::create([&]() {
		_chara[5]->changeFaceAnimation(eENDFACE::SMILE);
	});
	auto delay3 = DelayTime::create(1.0f);
	auto call5 = CallFunc::create([&]() {
		((EndingScene*)this->getParent())->replace(this);
	});

	auto seq = Sequence::create(delay1, call0, move0, call1, delay0, call2, ease0, call3, delay2, call4, delay3, call5, NULL);
	_chara[5]->runAction(seq);

	return true;
}