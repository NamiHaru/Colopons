#include "SaveData.h"

SaveData* SaveData::create()
{
	SaveData *pRet = new SaveData();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool SaveData::init() 
{
	if (!Node::init())return false;

	user = UserDefault::getInstance();

	return true;
};


//-----------------------------------------------------------------------------------------------------------------------------------------
//セーブ

//どこまでクリアしたか
void SaveData::saveClear(int clearNum)
{
	if (loadClear() < clearNum) 
	{
		user->setIntegerForKey(CLEARKEY, clearNum);
	}
	if (clearNum < 0)
	{
		user->setIntegerForKey(CLEARKEY, clearNum);
	}
};

//直前にどこをクリアしたか
void SaveData::saveLastClear(int clearNum) 
{
		user->setIntegerForKey(LASTCLEARKEY, clearNum);
};

//クリアしたグレード
void SaveData::saveGrade(int gradeNum) 
{
	if (loadGrade()>gradeNum)
		user->setIntegerForKey(GRADEKEY, gradeNum);
	if (gradeNum < 0)
	{
		user->setIntegerForKey(CLEARKEY, gradeNum);
	}
};

//直前にクリアした色
void SaveData::savePlayerColor(Color4F col) 
{
	int r = col.r * 255.0f;
	int g = col.g * 255.0f;
	int b = col.b * 255.0f;
	user->setIntegerForKey(COLOR_R_KEY, r);
	user->setIntegerForKey(COLOR_G_KEY, g);
	user->setIntegerForKey(COLOR_B_KEY, b);
};

//時間帯をセーブ
void SaveData::saveTimeZone(TIME_ZONE time) 
{
	user->setIntegerForKey(TIME_ZONE_KEY, (int)time);
};

//星が出るかどうか
void SaveData::saveStarAppear(bool is) 
{
	user->setBoolForKey(STAR_APPEAR_KEY, is);
}

// 空の色が変わった後にタイトルを見たかどうか。
void SaveData::saveLookedSky(bool is)
{
	user->setBoolForKey(LOOKED_SKY, is);
}

// すでにクリアーしているかどうか。
void SaveData::saveGameCleared(bool is)
{
	user->setBoolForKey(GAME_CLEARED, is);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//ロード

//どこまでクリアしたか
int SaveData::loadClear()
{
	return user->getIntegerForKey(CLEARKEY);
};

//直前にどこをクリアしたか
int SaveData::loadLastClear()
{
	return user->getIntegerForKey(LASTCLEARKEY);
};

//クリアしたグレード
int SaveData::loadGrade() 
{
	return user->getIntegerForKey(GRADEKEY);
};

//直前にクリアした色
Color4F SaveData::loadPlayerColor() 
{
	return Color4F(user->getIntegerForKey(COLOR_R_KEY), user->getIntegerForKey(COLOR_G_KEY), user->getIntegerForKey(COLOR_B_KEY),1.0f);
};

//直前までの時間帯
TIME_ZONE SaveData::loadTimeZone()
{
	return (TIME_ZONE)user->getIntegerForKey(TIME_ZONE_KEY);
};

//星が出ているか
bool SaveData::loadStarAppear() 
{
	return user->getBoolForKey(STAR_APPEAR_KEY);
};

//起動した回数
void SaveData::startUpNum()
{
	if (user->getIntegerForKey(START_UP_NUM_KEY) == 0)
		AllResset();
	user->setIntegerForKey(START_UP_NUM_KEY, user->getIntegerForKey(START_UP_NUM_KEY)+1);
};

//リセット
void SaveData::AllResset() 
{
	saveClear(-1);
	saveGrade(-1);
	saveLastClear(-1);
	savePlayerColor(Color4F::WHITE);
	saveTimeZone(TIME_ZONE::ZEROTIME);
	saveLookedSky(false);
	saveStarAppear(false);
	saveGameCleared(false);
};

// 空の色が変わった後にタイトルを見たかどうか。
bool SaveData::loadLookedSky()
{
	return user->getBoolForKey(LOOKED_SKY);
}

// 既にゲームをクリアーしているかどうか。
bool SaveData::loadGameCleared()
{
	return user->getBoolForKey(GAME_CLEARED);
}