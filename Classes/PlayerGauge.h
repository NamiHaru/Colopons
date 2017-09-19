#ifndef __PLAYER_GAUGE_H__
#define __PLAYER_GAUGE_H__

#include "cocos2d.h"

USING_NS_CC;

//プレイヤーの行動可能回数を可視化させたクラス
//決められた値に対して随時変更する
class PlayerGauge:public Node
{
public:
	static PlayerGauge* create(Vec2 pos);
	bool init(Vec2* vects, int segment, Color4F color);
	void update(float delta);


	Sprite* frameSp;//枠の画像
	Sprite* valueSp;//ゲージに使う画像


	int gaugeCount;//ゲージの表示



};

#endif // !__PLAYER_GAUGE_H__
