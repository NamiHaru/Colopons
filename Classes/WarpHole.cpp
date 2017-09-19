#include "WarpHole.h"


WarpHole* WarpHole::create(Vec2 spawnPos)
{
	WarpHole *pRet = new WarpHole();
	if (pRet && pRet->init(spawnPos))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool WarpHole::init(Vec2 spawnPos)
{
	if (!Node::init())
	{
		return false;
	}
	timer = 0;
	collider = 100.0f;

	mySprite = Sprite::create("Game/Warp/Warp.png");
	addChild(mySprite);

	setPosition(spawnPos);
	myPosition = spawnPos;
	log("warp[%0.0f,%0.0f]", myPosition.x, myPosition.y);
	DrawNode* d = DrawNode::create();
	addChild(d);
	d->drawCircle(Vec2(0, 0), collider, 0, 360, false, Color4F::GREEN);
	mySprite->runAction(RepeatForever::create(RotateBy::create(1, -360)));

	scheduleUpdate();

	log("size%d", targets.size());
	log("myPosition=[%0.0f,%0.0f]", myPosition.x,myPosition.y);

	return true;
};

void WarpHole::update(float delta)
{
	for (int i = 0; i < targets.size(); i++)
	{
		//ワープに当たっているやつの処理
		if(isHit)
		{
			//その場を去ったら辺り判定を開始する
			if (length(targets.at(0)->myPosition - myPosition) > collider)
			{
				//	hits._Pop_back_n(j);
				isHit = false;
			}
			else
				break;
		}
		//	log("length[%0.0f]", length(targets.at(i)->myPosition - myPosition));
		if (length(targets.at(i)->myPosition - myPosition) <= collider)
		{
			//hits.push_back(i);
			if (!partner->isHit) {
				partner->isHit = true;
			}
			objectWarp(targets.at(i)->myPosition, partnerPosition);
			//log("warp");
			//timer = 0;
		}
	}
};


//対象が自身に衝突したらその対象を瞬間移動させる
//当たり続けている場合は無効になる
void WarpHole::objectWarp(Vec2& target, Vec2& partner) 
{
	target = partner;
};
