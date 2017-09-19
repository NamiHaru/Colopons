#ifndef _EndingScene_h_
#define _EndingScene_h_

#include "cocos2d.h"
#include "SaveData.h"
#include "SoundSystem.h"

enum class eLAYER
{
	OPEN = 0,
	START,
	TITLE
};

class EndingScene : public cocos2d::Scene
{
public:
	static EndingScene* createLayer(eLAYER el = eLAYER::OPEN);
	bool init();
	CREATE_FUNC(EndingScene);
	void replace(cocos2d::Layer* layer);

	cocos2d::Layer* _layer;
	SaveData* _saveData;
	SoundSystem* _soundSystem;

	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void replaceSelect();

private:
	bool _replacingLayer = false;
	bool _gameCleared;
	bool _isReplaceScene = false;
	
	eLAYER _nowLayer;
	cocos2d::Sprite* _fadeSp;
};

#endif