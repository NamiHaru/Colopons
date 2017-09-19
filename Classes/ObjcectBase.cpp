#include "ObjectBase.h"

//初期設定
void ObjectBase::initialize(Vec2 pos) 
{
	setPosition(pos);
	myPosition = pos;
};

//画像を中央にして自身の画像を置く
void ObjectBase::initWithFileCenter(std::string body, std::string head, Size chipSize,float delay)
{
	mySprite = CharacterAnimation::create(body, head,chipSize, delay);
	addChild(mySprite, 5);
};

//キャラクターpとの範囲円が重なっているか
float ObjectBase::onCollision(ObjectBase* p)
{
	return onCollisionCircle(this->myPosition, this->objectRange, p->myPosition, p->objectRange);
};

//posから半径range内にいるか
bool ObjectBase::onCollision(Vec2 pos, float range)
{
	if (length(pos - myPosition) <= range)
	{
		////log("length=%f,range=%f",length(pos-myPosition),range);
		return true;
	}
	return false;
};

//start-end間に当たっているかどうか
bool ObjectBase::onCollision(Vec2 start, Vec2 end,float range)
{
	Vec2 AB = end - start;
	Vec2 AP = myPosition - start;
	Vec2 BP = myPosition - end;

	//外積
	float APxAB = cross(AB,AP);
	if (APxAB < 0)APxAB *= -1;

	//内積
	float DotAP = dot(AP, AB);
	float DotBP = dot(BP, AB);

	if (AB.x*AB.x == 0 && AB.y*AB.y == 0)
	{
		log("out");
		return false;
	}
	float ans = APxAB / length(AB);

	if (ans < range)
	{
		if (DotAP*DotBP <= 0)
		{
			return true;
		}
		else
		{
			if (ans > length(AP) || ans>length(BP))
			{
				return true;
			}
			return false;
		}
	}
	else
	{
		return false;
	}
	return false;
};


//当たり判定のあるものを設定
void ObjectBase::setTarget(ObjectBase* p)
{
	targets.pushBack(p);
};

void ObjectBase::setObjectRange(float range) 
{
	objectRange = range;
}

