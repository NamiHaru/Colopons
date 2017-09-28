#ifndef __WARPHOLE_H__
#define __WARPHOLE_H__

#include "AllTags.h"
#include "ObjectBase.h"
#include "PlayerCloser.h"

using namespace std;

//対象が初回ヒット時にパートナーのホールにワープをさせる
//ワープ先のホールはキャラクターが離れるまで次回ワープを見逃す

//ワープホール単体
class Hole :public ObjectBase 
{
public:
	static Hole* create(Vec2 spawnPos);
	//初期設定
	virtual bool init(Vec2 spawnPos);
	//更新
	virtual void update(float delta);

	//変化アニメーション
	void playAnimation(bool startOrEnd);

	Sprite* mySprite;
	bool isHit;
};

//対になるワープホールの管理者
class WarpHole :public Node
{
public:
	static WarpHole* create(Vec2 w1, Vec2 w2,PlayerCloser* target);
	bool init(Vec2 w1, Vec2 w2,PlayerCloser* target);
	void update(float delta);
	
	void setTargetPlayers(PlayerCloser* p);
	//対象が自身に衝突したらその対象を瞬間移動させる
	//当たり続けている場合は無効になる
	void objectWarp(Character* target, Vec2& partner);
	void warpAnimation(Hole*start,Hole* end);
	bool onCollisionPlayers();


	PlayerCloser* player;//対象とするプレイヤー
	Hole *warp1, *warp2;//管理するワープホール
	bool inWarpMiddle;//ワープしている最中か

};

#endif // !__WARPHOLE_H__
