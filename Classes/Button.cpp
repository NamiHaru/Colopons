#include "Button.h"

#include "MainGameScene.h"
#include "TitleSelectScene.h"

Button* Button::create(int num)
{
	Button *pRet = new Button();
	if (pRet && pRet->init(num))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool Button::init(int num) 
{
	if (!Sprite::init())return false;
	buttonnum = num;

	if (num == 0) 
	{
		initWithFile("Game/Message/Retry_off.png");
		Sprite* effectSp = Sprite::create("Game/Message/Retry_off.png");
		effectSp->setPosition(Vec2(getBoundingBox().size.width*0.5f, getBoundingBox().size.height*0.5f));
		addChild(effectSp);

		ScaleTo* scaleUp = ScaleTo::create(1.0f, 1.3f);
		FadeOut* fadein = FadeOut::create(1.0f);
		Spawn* fech1 = Spawn::createWithTwoActions(scaleUp, fadein);
		ScaleTo* scaleOr = ScaleTo::create(0, 1);
		FadeOut* fadeout = FadeOut::create(0);
		Spawn* fech2 = Spawn::createWithTwoActions(scaleOr, fadeout);
		FadeIn* fadeZero = FadeIn::create(0);
		effectSp->runAction(RepeatForever::create(Sequence::create(fech1, fech2,fadeZero, nullptr)));
	}
	else
	{
		initWithFile("Game/Message/Exit_off.png");
	}


	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(Button::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Button::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Button::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);





	return true;
}

bool Button::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	if (getBoundingBox().containsPoint(touch->getLocation()))
	{
		if (buttonnum == 0) {
			setTexture("Game/Message/Retry.png");
		}
		else {
			setTexture("Game/Message/Exit.png");
		}
	}

	return true;
};

void Button::onTouchMoved(const Touch * touch, Event *unused_event)
{

};

void Button::onTouchEnded(const Touch * touch, Event *unused_event)
{
	if (buttonnum == 0)
	{
		setTexture("Game/Message/Retry_off.png");
	}else{
		setTexture("Game/Message/Exit_off.png");
	}
	if (getBoundingBox().containsPoint(touch->getLocation()))
	{
		if (buttonnum == 0) //もう一度
		{
			auto scene = MainGameScene::createScene(stagenum);
			auto transition = TransitionFade::create(1.0f, scene, color);
			Director::getInstance()->replaceScene(transition);
		}
		else//旅に出る
		{
			auto scene = TitleSelectScene::createSelectScene();
			auto transition = TransitionFade::create(3.0f, scene, Color3B::BLACK);
			Director::getInstance()->replaceScene(transition);
		}
	}
};
