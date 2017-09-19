#ifndef __PLAYER_ROBOT_H__
#define __PLAYER_ROBOT_H__

#include "cocos2d.h"
#include "Character.h"
#include "CutParticle.h"

#define MODE 0
#define MOVE_MAX 13

USING_NS_CC;

//なぞった方向に移動をする
//キャラクターが移動する軌道を一度に設定しておくことができるクラス
class PlayerRobot :public Character 
{
public:
	static PlayerRobot* create(Vec2 pos,Color4F col=Color4F(0,0,0,0));
	bool init(Vec2 pos,Color4F col);

	void plusAction();

	//角度の保存
	void setAngle(Vec2 from, Vec2 to);
	//歩き始める
	void moveStart();
	//つぎに行くべきところの設定
	void nextPosition();
	//次に行く場所がなくなった時に配列の中を削除し、動きを止める
	void stopPosition();
	//ゴールした時
	void findPosition();

	//止まった時のアニメーション
	void stopAnimation();
	//ゴールした時のアニメーション
	void findAnimation();


	//プレイヤーの操作が異なるので仮想化
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

	//一定区間超えた位置(起動設定に必要)
	Vec2 endPosition;
	//移動準備完了しているか
	bool isStandby;
	//次回の移動を決められたか
	bool isNext;
	//動いているか
	bool isMove;

	float checkTime;//コマの区切り
	//現在移動している区間番号
	int angleNum;
	//区間の軌道角度
	std::vector<float> angles;
	Sprite* messageSp;
	CutParticle* goalPa;
	ObjectBase* goal;
};
#endif // !__PLAYER_ROBOT_H__
