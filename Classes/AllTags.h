#ifndef __ALL_TAGS_H__
#define __ALL_TAGS_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define DIR_CHECK 45
#define PLAYER_AI 0
#define PLAYER_HANSOME 1
#define MASS_SIZE 24

static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1200);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

static float viewSize = 1.0f;

//二つの絶対座標
struct SEGMENT
{
public:
	Vec2 from, to;
	SEGMENT() {};
	SEGMENT(Vec2 vFrom, Vec2 vTo) 
	{
		from = vFrom;
		to = vTo-vFrom;
	}
};

static SEGMENT setSegment(Vec2 ms, Vec2 mv) 
{
	SEGMENT seg;
	seg.from = ms; seg.to = mv;
	return seg;
}

////絶対値化
//static float abs(float f)
//{
//	return (f<0)?f*=1:f;
//}

////正規化
static Vec2 normalize(Vec2 pos) 
{
	float mag = 1 / sqrt(pos.x*pos.x + pos.y*pos.y);
	pos.x *= mag;
	pos.y *= mag;
	return pos;
};

//長さ
static float length(Vec2 pos) 
{
	return sqrt(pos.x*pos.x + pos.y*pos.y);
};

//内積(単位はラジアン)
static float dot(Vec2 from, Vec2 to) 
{
	return ((from.x*to.x) +( from.y*to.y));
};

//外積
static float cross(Vec2 from, Vec2 to) 
{
	return ((from.x * to.y) -( from.y * to.x));
};

//デグリをラジアンに変換する(単位はΠ)
static float degToRag(float deg) 
{
	//ラジアン = 度 × 円周率 ÷ 180
	return deg*M_PI / 180;
}

//ラジアンをデグリに変換する(単位は度)
static float ragToDeg(float rag)
{
	//度 = ラジアン × 180 ÷ 円周率
	return rag * 180 / M_PI;
}

//二つの線分が交わっているか
static bool onCollisionCross(SEGMENT fromSegment, SEGMENT toSegment, float* outT1, float* outT2, Vec2* outPos)
{
	Vec2 to = toSegment.from - fromSegment.from;

	//平行かどうか
	float c = cross(fromSegment.to, toSegment.to);
	if (c == 0.0f)
	{
		//平衡状態である
		return false;
	}
	float cFrom = cross(to, fromSegment.to);
	float cTo = cross(to, toSegment.to);

	float tFrom = cFrom / c;
	float tTo = cTo / c;

	if (outT1)
		*outT1 = cFrom / c;
	if (outT2)
		*outT2 = cTo / c;

	const float eps = 0.00001f;
	if (tFrom + eps < 0 || tFrom - eps > 1 || tTo + eps < 0 || tTo - eps > 1) {
		// 交差していない
		return false;
	}

	if (outPos)
		*outPos = fromSegment.from + fromSegment.to * tFrom;

	return true;
};

//方向ベクトルから右方向に固有角度で自身の視認範囲のベクトルを取得する
static Vec2 getDirectionDegree(Vec2 target, float deg, float range=1.0f)
{
	Vec2 vector = normalize(target);
	//ラジアンに変換
	float rag = degToRag(deg);

	float ax = vector.x*cos(rag) - vector.y*sin(rag);
	float ay = vector.x*sin(rag) + vector.y*cos(rag);

	vector.x = ax*range;
	vector.y = ay*range;

	return vector;
};

static float onCollisionCircle(Vec2 posA, float circleA, Vec2 posB, float circleB) 
{
	if (pow(posA.x - posB.x, 2) + pow(posA.y - posB.y, 2)<=pow(circleA+circleB,2)) 
	{
		return pow(posA.x - posB.x, 2) + pow(posA.y - posB.y, 2) - pow(circleA + circleB, 2);
	}
	return 0;
};

enum GAMESTATE 
{
	SANDBY = 0,PLAY,MOVE_START,MOVING,MOVE_STOP,CLEAR,MISS
};

//キャラクターの動き
enum STATUS
{
	//立つ、歩く、止まる、追う、死ぬ
	STAND=0,MOVE,STOP,FIND,CHASE,DEATH
};

//向きの開始角
enum DIR_DEGREE
{
	DIR_RIGHT=0,DIR_UP=90,DIR_LEFT=180,DIR_DOWN=270,
};

enum TIME_ZONE 
{
	ZEROTIME=-1,MORNING = 1, EVENING = 4, NIGHT = 8, STAR
};

#endif // !__ALL_TAGS_H__
