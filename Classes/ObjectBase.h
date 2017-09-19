#ifndef __OBJECT_BASE_H__
#define __OBJECT_BASE_H__

#include "cocos2d.h"
#include "CharacterAnimation.h"
#include "AllTags.h"

USING_NS_CC;

//オブジェクトすべてにある機能
//歩いて移動する機能は持たない
//お互いの衝突判定はある予定
class ObjectBase :public Node 
{
public:	

	//初期設定
	void initialize(Vec2 pos);
	//初期画像を中心に配置
	void initWithFileCenter(std::string body, std::string head, Size chipSize = Size(100, 100),float delay=0.5f);
	//ターゲット範囲に入っているか
	virtual bool onCollision(Vec2 pos, float range);
	//自身と引数(相手)の円判定
	virtual float onCollision(ObjectBase* p);
	//赤外線判定
	virtual bool onCollision(Vec2 start, Vec2 end,float range);
	//当たり判定のあるものを設定
	void setTarget(ObjectBase* p);
	//衝突範囲の設定
	void setObjectRange(float range);

	//移動可能範囲を示す円環
	DrawNode* moveRangeSp;
	//自身の画像
	CharacterAnimation* mySprite;
	//自身の場所
	Vec2 myPosition;


	//自身と当たり判定のある物
	Vector<ObjectBase*> targets;

	float objectRange;//衝突範囲
};


#endif //! __OBJECT_BASE_H__
