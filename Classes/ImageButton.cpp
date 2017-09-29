#include "ImageButton.h"
USING_NS_CC;

bool ImageButton::init(bool strictJudgement)
{
	if (!Node::init())
	{
		return false;
	}
	
	// �^�b�`���ꂽ���Ƃ��擾����I�u�W�F�N�g
	auto listener = EventListenerTouchOneByOne::create();
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->setSwallowTouches(true);
	// �^�b�`���ꂽ�u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchBegan = CC_CALLBACK_2(ImageButton::onTouchBegan, this);
	// �^�b�`����Ă���ԌĂ΂�郁�\�b�h��o�^
	listener->onTouchMoved = CC_CALLBACK_2(ImageButton::onTouchMoved, this);
	// �^�b�`�������ꂽ�u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchEnded = CC_CALLBACK_2(ImageButton::onTouchEnded, this);
	// �C�x���g�̎��s�̗D�揇�ʂ��m�[�h�̏d�Ȃ菇�Ɉˑ�������
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