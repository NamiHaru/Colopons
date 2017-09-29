#ifndef _ResetButton_h_
#define _ResetButton_h_
#include "cocos2d.h"
#include "ImageButton.h"

class ResetButton : public ImageButton
{
public:
	static ResetButton* create(const cocos2d::String path, cocos2d::Color3B color = cocos2d::Color3B::WHITE);
	bool init();
	void buttonPushed() override;
};

#endif // !_ResetButton_h_
