#include "MovieBase.h"
#include "TitleSelectScene.h"

using namespace cocos2d;

MovieBase* MovieBase::create()
{
	MovieBase* pRet = new MovieBase();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool MovieBase::init()
{
	if (!Scene::init()) return false;

	// タッチされたことを取得するオブジェクト
	auto listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->setSwallowTouches(true);
	// タッチされた瞬間に呼ばれるメソッドを登録
	listener->onTouchBegan = CC_CALLBACK_2(MovieBase::onTouchBegan, this);
	// タッチされている間呼ばれるメソッドを登録
	//listener->onTouchMoved = CC_CALLBACK_2(MovieBase::onTouchMoved, this);
	// タッチが離された瞬間に呼ばれるメソッドを登録
	listener->onTouchEnded = CC_CALLBACK_2(MovieBase::onTouchEnded, this);
	// イベントの実行の優先順位をノードの重なり順に依存させる
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool MovieBase::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if(!_isSceneReplace) return true;
	return false;
}

void MovieBase::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	_isSceneReplace = true;
	auto scene = TitleSelectScene::createTitleScene();
	auto transition = TransitionFade::create(1.0f, scene, Color3B::WHITE);
	Director::getInstance()->replaceScene(transition);
}
