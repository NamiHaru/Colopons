#ifndef __WALL_H__
#define __WALL_H__

#include "cocos2d.h"
#include "AllTags.h"
#include "CutParticle.h"
#include "WallDust.h"

USING_NS_CC;

#define SQUARE_SIZE 4
#define POINT_SIZE 50

//線に挟まれたときに面積の少ないほうが消滅する壁
class Wall :public Node
{
public:
	static Wall* create(Rect rect, Color4F fillColor, Color4F segmentColor);
	bool init(Rect rect, Color4F fillColor, Color4F segmentColor);
	static Wall* create(Vec2* vecs,int count ,Color4F fillColor, Color4F segmentColor);
	bool init(Vec2* vecs,int count, Color4F fillColor, Color4F segmentColor);
	void update(float delta);

	int segmentCount;
	int drawCount;
	float dustSlope;
	float cutTimer;
	Vec2 points[POINT_SIZE];
	bool* playerCut;
	bool isCuted;
	DrawNode* myWall,*debug;
	ClippingNode* clipp;
	Color4F cutedColor;
	//判定を取る線
	Vec2 *fromPos,*toPos;
	CutParticle* particle;
	Sprite*clippSprite;

	//------------------------------------------
	//次はこれを使って分割処理をする
	//追加した位置の番号
	int addPointNum[2];
	//-----------------------------------------
	//カットした後の色を設定する
	void setCutedColor(Color4F cColor);
	
	void setTargets(Vec2* from,Vec2* to);
	//新しくポイントを設定する
	void setPoint(int number, Vec2 point);
	//切り取られるほうのポイントを設定する
	void setDustPoints(Vec2* dust);
	//衝突判定命令
	void callCollision();
	//from-to間の線とtargetの交点を調べる
	int checkPoint(Vec2* hitPos, float* s0Slope,SEGMENT s0, SEGMENT s1);
	//検出した点を追加して、配列の中に入れる
	void addPoint(Vec2* hitPos,Vec2* points,int toNum);
	//点の順番の入れ替え
	void swapPoint(Vec2* points,int one,int wto);
	//配列の中を先頭から3つずつ取り出した点で面積の合計を返す
	float sumArea(Vec2 seg[], int point[]);
	//角の頂点をなくして、その頂点をつないでいた線同士をつないだ5角形を作る
	void changePentagon(Vec2 *vPoint, int onePoint,int twoPoint);
	//切り取る場所検出
	void checkCutArea(Vec2* seg );
	//切り取った後に面積を再構築する視覚効果
	void rebuildingArea(Vec2 seg[], int corner);
	//切り取られたほうの面積を再構築して消えていく
	void rebuildingDust(Vec2 seg[], int corner);

	//切り取られる演出
	void cutEffect();
	//コピーする
	void copyPoints(Vec2* from, Vec2* out, int number);
	//順番を右回りに戻す
	void sortPoints(Vec2* points, int*nums);
	//壁の配列が規定より超えたときに超えた分だけ0から数える
	Vec2 getOverPoint(Vec2 points[],int limit,int num);
	//選択点と次の点との方向ベクトルを返す
	Vec2 getSegment(int startpoint);
};

#endif // !__WALL_H__
