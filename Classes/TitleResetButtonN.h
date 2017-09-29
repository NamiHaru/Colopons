#include "cocos2d.h"
#include "ImageButton.h"

class TitleResetButtonN : public ImageButton
{
public:
	static TitleResetButtonN* create();
	bool init();
	void buttonPushed() override;
};