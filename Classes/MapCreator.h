#ifndef __MAP_CREATOR_H__
#define __MAP_CREATOR_H__

#include "cocos2d.h"
#include "PlayerCloser.h"
#include "Goal.h"
#include "Wall.h"

#include <iostream>

//読み込みの長さ指定
//DATA_LENGTH_PLAYERのような感じ
#define D_L_PLAYER 16
#define D_L_GOAL 14
#define D_L_WALL 33
#define D_L_FLOOR 2048
#define D_FLOOR_LINE 8

#define TILE_SIZE 64

#define D_N_PLAYER 'P'
#define D_N_GOAL 'G'
#define D_N_WALL 'W'
#define D_N_FLOOR 'F'
#define D_N_NAME 'N'

using namespace std;

USING_NS_CC;

class MapCreator:public Node
{
private:

	//キャラクター
	//void createPlayer(float x, float y);

public:

	static MapCreator* create(int num,Color4F col);
	bool init(int num,Color4F col);

	//解析データ置き場
	char analyzeData[2048];

	//マップ情報
	PlayerCloser* robot;
	Goal* goal;
	Vector<String*> names;
	Vector<Wall*> walls;
	Vector<Node*> floors;
	Color4F playerColor;

	//マップ作成処理---------------------------------------------------------------------------
	//マップファイル読み込み
	void openMapFile(char* name,int num=0);
	//マップ情報管理関数
	void loadMap(string mapText);
	//マップ情報の追加
	void pushObject(Goal*& obj,String*& id);
	//マップ情報の追加
	void pushObject(Wall*& obj, String*& id);
	//マップ情報の追加
	void pushObject(Node*& obj, String*& id);
	//マップの配置
	void putObject(Character* &obj, Vec2 pos);
	//配置キャラの解析
	void analyzePlayer(char* data);
	void analyzeGoal(char* data);
	void analyzeWall(char* data);
	void analyzeObject(char* data);
	void analyzeFloor(char* data);
	//解析に使うための文字列の先頭アドレスを手に入れる
	char* getAnalyzeData(string text,int length);
	//文字列をfloat型で返す。
	float getCharToFloat(char* data,int length=4); 
	//文字列をint型で返す。
	int getCharToInt(char* data, int length=4);
	//16進数を10進数に戻す
	int getHexToInt(char* data,int length=1);
	//特定の文字を探して、配列内の番号を返す
	int getFindCharNumber(char* data,char find);
	//解析した文字に応じて方位を返す
	DIR_DEGREE getCharToDirction(char* dir);

	//--------------------------------------------------------------------------------------------------

	//マップ内の衝突関係処理
	void checkWall(Character* obj,Vector<Wall*>wall,float range);

	//レベルのセット
	void setLevel(int level);
	int getLevel();
	int mapLevel;


	//完成したマップを一つのレイヤーに統合して戻り値として返す
	Layer* printMap();

};


#endif // !__MAP_CREATOR_H__
