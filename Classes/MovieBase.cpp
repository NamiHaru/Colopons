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

	// �^�b�`���ꂽ���Ƃ��擾����I�u�W�F�N�g
	auto listener = EventListenerTouchOneByOne::create();
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->setSwallowTouches(true);
	// �^�b�`���ꂽ�u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchBegan = CC_CALLBACK_2(MovieBase::onTouchBegan, this);
	// �^�b�`����Ă���ԌĂ΂�郁�\�b�h��o�^
	//listener->onTouchMoved = CC_CALLBACK_2(MovieBase::onTouchMoved, this);
	// �^�b�`�������ꂽ�u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchEnded = CC_CALLBACK_2(MovieBase::onTouchEnded, this);
	// �C�x���g�̎��s�̗D�揇�ʂ��m�[�h�̏d�Ȃ菇�Ɉˑ�������
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
