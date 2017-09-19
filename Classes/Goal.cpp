#include "Goal.h"

Goal* Goal::create(Vec2 spawnPos,Color4F color) 
{
	Goal *pRet = new Goal();
	if (pRet && pRet->init(spawnPos,color))
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

bool Goal::init(Vec2 spawnPos,Color4F color) 
{
	if (!Node::init())return false;

	setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	initialize(spawnPos);
	myColor = color;


	mySprite = Sprite::create("Game/Jewel.png");
	mySprite->setColor(Color3B(color.r*255.0f,color.g*255.0f,color.b*255.0f));
	addChild(mySprite);

	mask = Sprite::create("Game/Jewel_mask.png");
	//BlendFunc addBlend = { GL_ONE_MINUS_DST_COLOR, GL_ONE };
	mask->setColor(Color3B(color.r*255.0f,color.g*255.0f,color.b*255.0f));
	//mask->setBlendFunc(addBlend);
	addChild(mask);

	/*draw = DrawNode::create();
	draw->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	addChild(draw);
	draw->clear();
	draw->drawDot(Vec2(0, 0), animationTimer, color);
	BlendFunc addBlend = { GL_SRC_ALPHA, GL_ONE };
	draw->setBlendFunc(addBlend);
*/

	goalTimer = 0.0f;

	scheduleUpdate();

	return true;
};

void Goal::update(float delta)
{
	animationTimer += 0.02f;
	if (animationTimer > 1.0f)
		animationTimer = -1.0f;
	//draw->clear();
	//draw->drawDot(Vec2(0, 0), cos(animationTimer*2.0f)*50.0f  ,myColor);
	mask->setScale(cos(animationTimer*2.0f)+0.5);
};

Color4F Goal::getStageColor() 
{
	return myColor;
};

float Goal::getAnimationScale() 
{
	return animationTimer;
};

void Goal::stopAnimation() 
{
	unscheduleUpdate();
};

bool Goal::drawGoalAction() 
{
	goalTimer += 1.0f/60.0f*255.0f;
	//draw->clear();
	//draw->drawDot(Vec2(0, 0), cos(animationTimer*2.0f)*25.0f + 50, myColor);
	for (int i = 0; i < 10; i++)
	{
		//draw->drawCircle(Vec2(0, 0), cos(animationTimer*2.0)*25.0f + 50 + goalTimer+i, 0, 360, false, Color4F(myColor.r, myColor.g, myColor.b, (255 - goalTimer) / 255.0f));
	}
	if (goalTimer >= 255.0f) {
		goalTimer = 0;		
		return true;
	}
	return false;
};

void Goal::setisGoalAddress(bool* is) 
{
	isGoal = is;
};
