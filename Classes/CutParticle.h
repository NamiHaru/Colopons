#ifndef __CUTPARTICLE_H__
#define __CUTPARTICLE_H__

#include "cocos2d.h"
#include "AllTags.h"

USING_NS_CC;

using namespace std;

class CutSingle :public Node 
{
public:
	static CutSingle* create(string name,Color4F color,float scaletimer, float decaytimer=1.0f, float emissionrotate=0);
	bool init(string name,Color4F color,float scaletimer, float decaytimer, float emissionrotate);
	void update(float delta);
	//各パラメータ
	//---------------------------------------------------------------------------
	//それぞれを制御するタイマー
	float allTimer;
	//大きさ
	float scaleTimer;
	//終了速度
	float decayTimer;
	//放射角度
	float emissionRotate;
	//終了したか
	bool isEnd;
	//画像
	Sprite* mySprite;
	//---------------------------------------------------------------------------

};

class CutParticle :public Node
{
public:
	static CutParticle* create(string name,int num,float scale, Color4F baseColor = Color4F::WHITE);
	bool init(string name,int num,float scale, Color4F baseColor = Color4F::WHITE);
	void update(float delta);
	void createParticle();
	void startParticle();
	void stopParticle();
	void setLine(Vec2 from, Vec2 to);
	void setParticleColor(Color4F color);
	Vec2 getRandoLine(float alpha);
	//---------------------------------------------------------------------------
	Vec2 fromPosition;
	Vec2 toPosition;
	//パーティクルの画像の名前
	string spriteName;
	//パーティクルの生成数
	int absoluteNumber;
	//大きさ
	float scaleMax;
	//ループさせるか
	bool isRoop;
	//パーティクルの色
	Color4F particleColor;
	//---------------------------------------------------------------------------
	Vector<CutSingle*> cuts;

};

#endif //!__CUTPARTICLE_H__
