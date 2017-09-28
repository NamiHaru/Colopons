#include "WarpHole.h"


Hole* Hole::create(Vec2 spawnPos)
{
	Hole *pRet = new Hole();
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

bool Hole::init(Vec2 spawnPos)
{
	if (!Node::init())
	{
		return false;
	}
	objectRange = 75.0f;

	mySprite = Sprite::create("Game/Warp/Warp.png");
	addChild(mySprite);

	setPosition(spawnPos);
	myPosition = spawnPos;
	//log("warp[%0.0f,%0.0f]", myPosition.x, myPosition.y);
	//DrawNode* d = DrawNode::create();
	//addChild(d);
	//d->drawCircle(Vec2(0, 0), objectRange, 0, 360, false, Color4F::GREEN);
	mySprite->runAction(RepeatForever::create(RotateBy::create(1, -360)));

	scheduleUpdate();

	//log("size%d", targets.size());
	//log("myPosition=[%0.0f,%0.0f]", myPosition.x,myPosition.y);



	return true;
};

void Hole::update(float delta)
{

};


void Hole::playAnimation(bool startOrEnd) 
{
	Sprite* sp = Sprite::create("Game/Warp/WarpInto.png");
	addChild(sp);
	if (startOrEnd) 
	{
		ScaleTo* scale = ScaleTo::create(1.0f, 3);
		FadeOut* fade = FadeOut::create(1.0f);
		Spawn* fech = Spawn::createWithTwoActions(scale, fade);
		RemoveSelf* remove = RemoveSelf::create();

		sp->runAction(Sequence::create(fech, remove, nullptr));
	}
	else 
	{
		ScaleTo* scale = ScaleTo::create(1.0f, 0);
		FadeOut* fade = FadeOut::create(1.0f);
		Spawn* fech = Spawn::createWithTwoActions(scale, fade);
		RemoveSelf* remove = RemoveSelf::create();

		sp->runAction(Sequence::create(fech, remove, nullptr));
	}
};


WarpHole* WarpHole::create(Vec2 w1, Vec2 w2,PlayerCloser* target) 
{
	WarpHole *pRet = new WarpHole();
	if (pRet && pRet->init(w1,w2,target))
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

bool WarpHole::init(Vec2 w1, Vec2 w2,PlayerCloser* target) 
{
	if (!Node::init())return false;

	warp1 = Hole::create(w1);
	addChild(warp1);
	warp2 = Hole::create(w2);
	addChild(warp2);

	setTargetPlayers(target);

	inWarpMiddle = false;

	scheduleUpdate();

	return true;
};

void WarpHole::update(float delta) 
{
	onCollisionPlayers();
	//“–‚½‚Á‚Ä‚¢‚é‚©


};

void WarpHole::setTargetPlayers(PlayerCloser* p) 
{
	player = p;
};

//‘ÎÛ‚ªŽ©g‚ÉÕ“Ë‚µ‚½‚ç‚»‚Ì‘ÎÛ‚ðuŠÔˆÚ“®‚³‚¹‚é
//“–‚½‚è‘±‚¯‚Ä‚¢‚éê‡‚Í–³Œø‚É‚È‚é
void WarpHole::objectWarp(Character* target, Vec2& partner)
{
	target->targetPosition = (target->myPosition - target->targetPosition) + partner;
	target->startPosition = (target->myPosition-target->startPosition) + partner;
};

void WarpHole::warpAnimation(Hole* start,Hole* end) 
{
	start->playAnimation(true);
	end->playAnimation(false);
};

bool WarpHole::onCollisionPlayers()
{
	bool isHit = false;
	Character* c;
	Vec2 pos;
	Hole* one, *two;

	if (onCollisionCircle(player->rightRobot->myPosition, player->rightRobot->objectRange, warp1->myPosition, warp1->objectRange))
	{
		c = player->rightRobot;
		pos = warp2->myPosition;
		isHit = true;
		one = warp2;
		two = warp1;
	}
	else if (onCollisionCircle(player->rightRobot->myPosition, player->rightRobot->objectRange, warp2->myPosition, warp2->objectRange))
	{
		c = player->rightRobot;
		pos = warp1->myPosition;
		isHit = true;
		one = warp1;
		two = warp2;
	}
	if (onCollisionCircle(player->leftRobot->myPosition, player->leftRobot->objectRange, warp1->myPosition, warp1->objectRange))
	{
		c = player->leftRobot;
		pos = warp2->myPosition;
		isHit = true;	
		one = warp2;
		two = warp1;
	}
	else if (onCollisionCircle(player->leftRobot->myPosition, player->leftRobot->objectRange, warp2->myPosition, warp2->objectRange))
	{
		c = player->leftRobot;
		pos = warp1->myPosition;
		isHit = true;
		one = warp1;
		two = warp2;
	}

	if (!isHit) 
	{
		inWarpMiddle = false;
	}
	else 
	{
		if (!inWarpMiddle)
		{
			objectWarp(c, pos); 
			warpAnimation(one,two);
			inWarpMiddle = true;
		}
	}
	return isHit;
};
