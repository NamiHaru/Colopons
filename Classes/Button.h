#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "cocos2d.h"

USING_NS_CC;

class Button :public Sprite 
{
public :
	static Button* create(int num);
	bool init(int num);


	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

	String* name;
	int buttonnum;
	int stagenum;
	Color3B color;
	bool on;

};


#endif //!__BUTTON_H__
