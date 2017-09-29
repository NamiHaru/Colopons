#include "Movie3.h"
#include "AllTags.h"
#include "ColorEnum.h"
#include "TitleSelectScene.h"
#include "Picture.h"
#include "MovieBase.h"

using namespace cocos2d;

bool Movie3::init()
{
	if (!Layer::init()) return false;

	auto back = Sprite::create("Select/SelectBackground.png");
	back->setPosition(designResolutionSize*0.5f);
	this->addChild(back);

	// ベジェ曲線のために３点を設定
	_bezierPos[0] = Vec2(0, -designResolutionSize.height*0.1f);
	_bezierPos[1] = Vec2(designResolutionSize.width*0.5f, -designResolutionSize.height*0.2f);
	_bezierPos[2] = Vec2(designResolutionSize.width, -designResolutionSize.height*0.1f);

	// ベジェ曲線を引く・Picture配置
	float f = 0.0f;
	Vec2 vec, vec1;
	Vec2 basePos = Vec2(0, 0);
	DrawNode *node = DrawNode::create();
	Picture* picture;

	basePos.y = designResolutionSize.height*0.75f;
	picture = Picture::create(0, false);
	drawBezier(node, 50, basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
	float p = 1.0f / (1 + 1);
	Vec2 b = bezier(p*(1), basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
	picture->setPosition(b);
	picture->setPos(b);

	this->addChild(node);
	this->addChild(picture);

	_char2 = CharacterAnimation::create("Character/TitleAnim_Body.png", "Character/TitleAnim_Head.png", Size(260, 260));
	_char2->stopAllAnimation(DIR::FRONT);
	_char2->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f);
	_char2->setVisible(false);
	this->addChild(_char2);

	_charAnim = CharacterAnimation::create("Character/TitleAnim_Body.png", "Character/TitleAnim_Head.png", Size(260, 260));
	_charAnim->startAnimation(DIR::RIGHT);
	_charAnim->setPosition(designResolutionSize.width*-0.2f, designResolutionSize.height*0.1f);
	this->addChild(_charAnim);

	auto move = MoveTo::create(6.0f, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.1f));
	auto call = CallFunc::create([&]() {
		_charAnim->stopAllAnimation(DIR::BACK);
	});
	auto delay = DelayTime::create(2.0f);
	auto call1 = CallFunc::create([&]() {
		_char2->setVisible(true);
	});
	auto delay1 = DelayTime::create(0.5f);
	auto call2 = CallFunc::create([&]() {
		_charAnim->startAnimation(DIR::RIGHT);
	});
	auto move0 = MoveTo::create(0.3f, Vec2(designResolutionSize.width*0.6f, designResolutionSize.height*0.1f));
	auto call3 = CallFunc::create([&]() {
		_charAnim->stopAllAnimation(DIR::LEFT);
	});
	auto call0 = CallFunc::create([&]() {
		auto scene = TitleSelectScene::createTitleScene();
		auto transition = TransitionFade::create(2.0f, scene);
		Director::getInstance()->replaceScene(transition);
	});
	auto seq = Sequence::create(move, call, delay, call1, delay1, call2, move0, call3, NULL);
	_charAnim->runAction(seq);

	auto delay0 = DelayTime::create(9.5f);
	auto move1 = MoveTo::create(3.0f, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.1f));
	auto seq1 = Sequence::create(delay0, move1, call0, NULL);
	_char2->runAction(seq1);

	return true;
}

void Movie3::update(float delta)
{

}

Movie3* Movie3::create()
{
	auto pRet = new Movie3();
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

Scene* Movie3::createScene()
{
	auto scene = MovieBase::create();
	Movie3* Movie3 = Movie3::create();
	scene->addChild(Movie3);
	return scene;
}

// ベジェ曲線描画用関数
Vec2 Movie3::bezier(float per, Vec2 pos0, Vec2 pos1, Vec2 po2)
{
	pos0.x = (1 - per)*(1 - per)*pos0.x + 2 * (1 - per)*per*pos1.x + per*per*po2.x;
	pos0.y = (1 - per)*(1 - per)*pos0.y + 2 * (1 - per)*per*pos1.y + per*per*po2.y;
	return pos0;
}
void Movie3::drawBezier(DrawNode* dn, int seg, Vec2 pos0, Vec2 pos1, Vec2 pos2)
{
	float per = 0.0f;
	float f = 1.0f / seg;
	Vec2 vec0, vec1;
	for (int i = 0; i <= seg; i++)
	{
		vec0 = bezier(per, pos0, pos1, pos2);
		per = f*i;
		vec1 = bezier(per, pos0, pos1, pos2);
		dn->drawSegment(vec0, vec1, 5, Color4F::BLACK);
	}
}