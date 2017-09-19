#ifndef __SAVEDATA_H__
#define __SAVEDATA_H__

#include	 "cocos2d.h"
#include "AllTags.h"

USING_NS_CC;

#define GAME_CLEAR_NUM 9

class SaveData :public Node 
{
public:
	const char* CLEARKEY = "clear";//クリアした数
	const char* LASTCLEARKEY = "lastclear";//最後にクリアした数
	const char* GRADEKEY = "grade";//できたランク
	const char* COLOR_R_KEY = "colorR";//r
	const char* COLOR_G_KEY = "colorG";//g
	const char* COLOR_B_KEY = "colorB";//b
	const char* TIME_ZONE_KEY = "time";//時間帯
	const char* STAR_APPEAR_KEY = "star";//星が出ていいか
	const char* START_UP_NUM_KEY = "startnum";//起動回数
	const char* LOOKED_SKY = "changeSky";// 空の色が変わった後にタイトルを見たかどうか。
	const char* GAME_CLEARED = "gameCleared";// 既にクリアーしているかどうか。
	UserDefault* user;

	static SaveData* create();
	bool init();

	void saveClear(int clearNum);
	void saveLastClear(int clearNum);
	void saveGrade(int gladeNum);
	void savePlayerColor(Color4F col);
	void saveTimeZone(TIME_ZONE time);
	void saveStarAppear(bool is);
	void saveLookedSky(bool is);
	void saveGameCleared(bool is);
	
	int loadClear();
	int loadLastClear();
	int loadGrade();
	Color4F loadPlayerColor();
	TIME_ZONE loadTimeZone();
	bool loadStarAppear();
	void startUpNum();
	bool loadLookedSky();
	bool loadGameCleared();

	void AllResset();
};

#endif // !__SAVEDATA_H__


