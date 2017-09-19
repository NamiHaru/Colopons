#ifndef __WARPHOLE_H__
#define __WARPHOLE_H__

#include "AllTags.h"
#include "ObjectBase.h"

using namespace std;

class WarpHole :public ObjectBase 
{
public:
	static WarpHole* create(Vec2 spawnPos);
	//‰Šúİ’è
	virtual bool init(Vec2 spawnPos);
	//XV
	virtual void update(float delta);

	Vec2 myPosition;
	Vec2 partnerPosition;
	WarpHole* partner;
	bool isHit;
	float collider;
	float timer;
	vector<int> hits;
	Sprite* mySprite;

	//‘ÎÛ‚ª©g‚ÉÕ“Ë‚µ‚½‚ç‚»‚Ì‘ÎÛ‚ğuŠÔˆÚ“®‚³‚¹‚é
	//“–‚½‚è‘±‚¯‚Ä‚¢‚éê‡‚Í–³Œø‚É‚È‚é
	void objectWarp(Vec2& target, Vec2& partner);




};


#endif // !__WARPHOLE_H__
