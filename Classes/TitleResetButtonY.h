#include "cocos2d.h"
#include "ImageButton.h"

class TitleResetButtonY : public ImageButton
{
public:
	static TitleResetButtonY* create();
	bool init();
	void buttonPushed() override;
};