#include "EndTitle.h"
#include "WoodScroll.h"
#include "TitleScroll.h"
#include "CharacterAnimation.h"
#include "AllTags.h"
#include "ColorEnum.h"
#include "EndingScene.h"

using namespace cocos2d;
using namespace std;

bool EndTitle::init()
{
	if (!Layer::init()) return false;

	Rect rect = Rect(0, 0, designResolutionSize.width, designResolutionSize.height);
	Sprite* sky = Sprite::create();
	sky->setTextureRect(rect);
	sky->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(sky);
	
	float decoSpeed = 0.05f;

	sky->setColor(getColorCode(eColor::INDIGO));
	ScrollSprite*  deco = ScrollSprite::create("Title/Star.png", decoSpeed, ScrollSprite::eOrientation::landscape, getColorCode(eColor::YELLOW));
	this->addChild(deco);

	auto ws = WoodScroll::create(-1.2f, 10);
	this->addChild(ws);

	auto ts = TitleScroll::create(-3.0f, 10);
	this->addChild(ts);

	auto colopon = CharacterAnimation::create("Character/TitleAnim_Body.png", "Character/TitleAnim_Head.png", Size(260, 260));
	this->addChild(colopon);
	colopon->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.18f);
	colopon->setDir(DIR::LEFT);
	colopon->getPon()->setColor(getColorCode(eColor::YELLOW));

	_map = Sprite::create("Ending/StuffRoll0.png");
	//_map->setOpacity(0);
	_map->setPosition(designResolutionSize * 0.5f);
	this->addChild(_map);

	this->scheduleUpdate();

	return true;
}

void EndTitle::update(float delta)
{
	_timer += delta * _diff;
	float per;
	if (_timer >= _MOVE_TIME) per = 1.0f;
	else if (_timer <= 0) per = 0.0f;
	else per = _timer / _MOVE_TIME;

	_map->setOpacity(255 * per);

	if (_diff > 0)
	{
		if (_timer > _MOVE_TIME + _STOP_TIME)
		{
			if (_COUNT - 1 > _cnt)
			{
				_diff *= -1;
				_timer -= _STOP_TIME;
				//_timer = 0.0f;
			}
			else
			{
				this->unscheduleUpdate();
				((EndingScene*)this->getParent())->replaceSelect();
			}
		}
	}
	else
	{
		if (_timer <= -_STOP_TIME)
		{
			_cnt++;
			String* spritePath = String::createWithFormat("Ending/StuffRoll%d.png", (int)_cnt);
			auto sp = Sprite::create(spritePath->getCString());
			_map->setTexture(sp->getTexture());
			_map->setOpacity(0);
			_timer = 0.0;
			_diff *= -1;
		}
	}
}