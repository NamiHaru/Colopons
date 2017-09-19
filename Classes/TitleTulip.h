#ifndef _TitleTulip_h_
#define _TitleTulip_h_

#include "cocos2d.h"
#include "Tulip.h"

class TitleTulip : public cocos2d::Node
{
public:
	bool init(int clearedStage);
	static TitleTulip* create(int clearedStage);

	const int TULIP_NUM = 5;
	Tulip* _tulip[5];
	void update(float delta);
};

#endif // !_TitleTulip_h_
