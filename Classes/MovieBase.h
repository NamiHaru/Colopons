#ifndef _MovieBase_h_
#define _MovieBase_h_

#include "cocos2d.h"

class MovieBase : public cocos2d::Scene
{
public:
	static MovieBase* create();
	bool init();

	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	//virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
protected:
	bool _isSceneReplace = false;
};

#endif // !_MovieBase_h_
