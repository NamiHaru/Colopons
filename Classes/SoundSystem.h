#ifndef _SoundSystem_
#define _SoundSystem_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class SoundSystem : public cocos2d::Node
{
public:
	static SoundSystem* create();
	bool init();
	void playBGM(std::string filePath, bool loops = true);
	void playSE(std::string filePath, bool loops = false, float pitch = 1.0f);
	void preloadBGM(std::string filePath);
	void preloadSE(std::string filePath);
	void setVolumeBGM(float volume);
	float getVolumeBGM();
	void setVolumeSE(float volume);
	float getVolumeSE();

private:
	CocosDenshion::SimpleAudioEngine* audio;
};

#endif // !_SoundSystem_

