#ifndef _TitleBatterfly_h_
#define _TitleBatterfly_h_

#include "cocos2d.h"
#include "Batterfly.h"

class TitleBatterfly : public cocos2d::Node
{
public :
	bool init(int clearedStage);
	static TitleBatterfly* create(int clearedStage);

	Batterfly* _batterfly[2];
};

#endif // !_TitleBatterfly_h_
