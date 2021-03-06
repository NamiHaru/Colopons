#include "SoundSystem.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

SoundSystem* SoundSystem::create()
{
	SoundSystem *pRet = new SoundSystem();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool SoundSystem::init()
{
	if (!Node::init())
	{
		return false;
	}

	audio = CocosDenshion::SimpleAudioEngine::getInstance();

	audio->setBackgroundMusicVolume(0.5f);

	audio->setEffectsVolume(0.5f);

	return true;
}

void SoundSystem::playBGM(string filePath, bool loops)
{
	// BGMの場合
	audio->playBackgroundMusic(filePath.c_str(), loops);
}

void SoundSystem::playSE(string filePath, bool loops, float pitch)
{
	// EFFECTの場合
	audio->playEffect(filePath.c_str(), loops, pitch);
}

void SoundSystem::preloadBGM(string filePath)
{
	// BGMの場合
	audio->preloadBackgroundMusic(filePath.c_str());
}

void SoundSystem::preloadSE(string filePath)
{
	// EFFECTの場合
	audio->preloadEffect(filePath.c_str());
}

void SoundSystem::setVolumeBGM(float volume)
{
	// BGMの場合
	audio->setBackgroundMusicVolume(volume);
}

float SoundSystem::getVolumeBGM()
{
	// BGMの場合
	return (audio->getBackgroundMusicVolume());
}

void SoundSystem::setVolumeSE(float volume)
{
	// EFFECTの場合
	audio->setEffectsVolume(volume);
}

float SoundSystem::getVolumeSE()
{
	// EFFECTの場合
	return audio->getEffectsVolume();
}