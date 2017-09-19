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
	// BGM�̏ꍇ
	audio->playBackgroundMusic(filePath.c_str(), loops);
}

void SoundSystem::playSE(string filePath, bool loops, float pitch)
{
	// EFFECT�̏ꍇ
	audio->playEffect(filePath.c_str(), loops, pitch);
}

void SoundSystem::preloadBGM(string filePath)
{
	// BGM�̏ꍇ
	audio->preloadBackgroundMusic(filePath.c_str());
}

void SoundSystem::preloadSE(string filePath)
{
	// EFFECT�̏ꍇ
	audio->preloadEffect(filePath.c_str());
}

void SoundSystem::setVolumeBGM(float volume)
{
	// BGM�̏ꍇ
	audio->setBackgroundMusicVolume(volume);
}

float SoundSystem::getVolumeBGM()
{
	// BGM�̏ꍇ
	return (audio->getBackgroundMusicVolume());
}

void SoundSystem::setVolumeSE(float volume)
{
	// EFFECT�̏ꍇ
	audio->setEffectsVolume(volume);
}

float SoundSystem::getVolumeSE()
{
	// EFFECT�̏ꍇ
	return audio->getEffectsVolume();
}