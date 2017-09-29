#include "ImageButton.h"
USING_NS_CC;

bool ImageButton::init(bool strictJudgement)
{
	if (!Node::init())
	{
		return false;
	}
	
	// タッチされたことを取得するオブジェクト
	auto listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->setSwallowTouches(true);
	// タッチされた瞬間に呼ばれるメソッドを登録
	listener->onTouchBegan = CC_CALLBACK_2(ImageButton::onTouchBegan, this);
	// タッチされている間呼ばれるメソッドを登録
	listener->onTouchMoved = CC_CALLBACK_2(ImageButton::onTouchMoved, this);
	// タッチが離された瞬間に呼ばれるメソッドを登録
	listener->onTouchEnded = CC_CALLBACK_2(ImageButton::onTouchEnded, this);
	// イベントの実行の優先順位をノードの重なり順に依存させる
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	_strictJudgement = strictJudgement;

	return true;
}

bool ImageButton::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	Rect rect = this->getBoundingBox();
	Point pos = pTouch->getLocation();
	if (rect.containsPoint(pos))
	{
		_onButton();
		return true;
	}
	return false;
}

void ImageButton::onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	if (_strictJudgement)
	{
		Rect rect = this->getBoundingBox();
		Point pos = pTouch->getLocation();
		if (!rect.containsPoint(pos))
		{
			_removeButton();
		}
	}	
}

void ImageButton::onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	Rect rect = this->getBoundingBox();
	Point pos = pTouch->getLocation();
	if (rect.containsPoint(pos) && _isPressed)
	{
		buttonPushed();
	}
	_removeButton();
}

void ImageButton::_onButton()
{
	color = this->getColor();
	this->setColor(Color3B::GRAY);
	_isPressed = true;
}

void ImageButton::_removeButton()
{
	this->setColor(color);
	_isPressed = false;
}