#include "GateScene.h"


GateScene* GateScene::createScene()
{
	GateScene *pRet = new GateScene();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
};

bool GateScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Sprite* p = Sprite::create("GateBack.png");
	p->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f));
	addChild(p);

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(GateScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GateScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GateScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
};


bool GateScene::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	if (touch->getLocation().x > designResolutionSize.width*0.5f)
	{
		Director::getInstance()->replaceScene(MainGameScene::createScene(0));
	}
	else
	{
		Director::getInstance()->replaceScene(TitleSelectScene::createTitleScene());
	};


	return true;
};

void GateScene::onTouchMoved(const Touch * touch, Event *unused_event)
{

};

void GateScene::onTouchEnded(const Touch * touch, Event *unused_event)
{

};
