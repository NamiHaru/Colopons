#include "PlayerCloser.h"

PlayerCloser* PlayerCloser::create(Vec2 right,Vec2 left,Color4F col)
{
	PlayerCloser *pRet = new PlayerCloser();
	if (pRet && pRet->init(right, left,col))
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

bool PlayerCloser::init(Vec2 right,Vec2 left,Color4F col) 
{
	if (!Node::init())return false;


	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(PlayerCloser::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerCloser::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerCloser::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	infraredLine = DrawNode::create();
	addChild(infraredLine);

	moveLineRight = DrawNode::create();
	addChild(moveLineRight);
	moveLineLeft = DrawNode::create();
	addChild(moveLineLeft);

	infraredEffect = DrawNode::create();
	addChild(infraredEffect);

	rightRobot = PlayerRobot::create(right,col);
	addChild(rightRobot);
	rightRobot->setTag(0);
	leftRobot = PlayerRobot::create(left,col);
	addChild(leftRobot);
	leftRobot->setTag(1);

	rightRobot->setTarget(leftRobot);
	leftRobot->setTarget(rightRobot);

	myColor = col;

	endRightPosition = right;
	endLeftPosition = left;

	rightRobot->scheduleUpdate();
	leftRobot->scheduleUpdate();

	delayTimer = 2.0f;
	isRobotMoving = false;
	isGoal = false;

	//scheduleUpdate();

	return true;
};

void PlayerCloser::update(float delta)
{

	delayTimer += 1.0f / 60.0f;
	if (delayTimer != 0)isRobotMoving = false;

	infraredLine->clear();
	//infraredLine->drawSegment(Vec2(rightRobot->myPosition.x, rightRobot->myPosition.y+80),Vec2(leftRobot->myPosition.x,leftRobot->myPosition.y+80), 4, Color4F::RED);

	effectTimer += 5.0f;
		infraredEffect->clear();
		infraredEffect->drawSegment(rightRobot->myPosition, leftRobot->myPosition, effectTimer / 255.0f * 8, Color4F(myColor.r, myColor.g, myColor.b, 255.0f - effectTimer / 225.0f));
		if (effectTimer >= 225.0f)
		{
			effectTimer = 0;
		}
	
	if (rightRobot->myState == STATUS::FIND&&leftRobot->myState == STATUS::FIND)
	{
		isGoal = true;
	}
	if (!rightRobot->isMove&&!leftRobot->isMove)
	{
		drawMoveLineRight();
		drawMoveLineLeft();
	}
	delayTimer += 1.0f / 60.0f;
	//		log("del=%f", delayTimer);
};

//右のロボットが進む軌道の表示
void PlayerCloser::drawMoveLineRight()
{
	Vec2 start = rightRobot->myPosition,end=rightRobot->myPosition;
	moveLineRight->clear();
	for (int i =0; i < rightRobot->angles.size(); i++) 
	{
		end = getDirectionDegree(Vec2(1,0), rightRobot->angles.at(i),rightRobot->doubtDegree)+start;
		//moveLineRight->drawDot(touch, 10, Color4F::BLACK);
		if (i >= rightRobot->angleNum) 
		{
			//タッチした位置から前回の位置
		//	moveLineRight->drawSegment(end, start, 6, Color4F::WHITE);
			moveLineRight->drawSegment(end, start, 5, 
				Color4F((float)i / (float)rightRobot->angles.size(), (float)i / (float)rightRobot->angles.size(), (float)i / (float)rightRobot->angles.size(), 1));

			//前回の位置から前々回の位置
			//moveLineRight->drawSegment(rightRobot->endPosition, rightRobot->startPosition, 3, Color4F::BLACK);
		}
		start = end;
	}
	if (rightRobot->isMoveWait)
	moveLineRight->drawSegment(end, endRightPosition, 5, Color4F::GRAY);
	//rightRobot->isPut = false;
};

//左のロボットが進む軌道を表示
void PlayerCloser::drawMoveLineLeft()
{
	Vec2 start = leftRobot->myPosition,end=leftRobot->myPosition;
	moveLineLeft->clear();
	for (int i = 0; i < leftRobot->angles.size(); i++)
	{
		end = getDirectionDegree(Vec2(1, 0), leftRobot->angles.at(i), leftRobot->doubtDegree) + start;
		//moveLineLeft->drawDot(touch, 10, Color4F::BLACK);
		if (i >= leftRobot->angleNum)
		{
			//タッチした位置から前回の位置
		//	moveLineLeft->drawSegment(end, start, 6, Color4F::WHITE);
			moveLineLeft->drawSegment(end, start, 5,
				Color4F((float)i / (float)leftRobot->angles.size(), (float)i / (float)leftRobot->angles.size(), (float)i / (float)leftRobot->angles.size(),1));
			//前回の位置から前々回の位置
			//moveLineLeft->drawSegment(leftRobot->endPosition, leftRobot->startPosition, 3, Color4F::BLACK);
		}
		start = end;
	}
	if(leftRobot->isMoveWait)
	moveLineLeft->drawSegment(end, endLeftPosition, 5, Color4F::GRAY);
	//leftRobot->isPut = false;
};

void PlayerCloser::startRobot() 
{
		rightRobot->moveTimer = 0;
		leftRobot->moveTimer = 0;
		moveLineRight->clear();
		moveLineLeft->clear();
		rightRobot->moveStart();
		leftRobot->moveStart();
};
bool PlayerCloser::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	if (rightRobot->isMoveWait)endRightPosition = touch->getLocation();
	if (leftRobot->isMoveWait)endLeftPosition = touch->getLocation();

	return true;
};

void PlayerCloser::onTouchMoved(const Touch * touch, Event *unused_event) 
{
	if (rightRobot->isMoveWait&&rightRobot->angles.size()<MOVE_MAX)endRightPosition = touch->getLocation();
	if (leftRobot->isMoveWait&&leftRobot->angles.size()<MOVE_MAX)endLeftPosition = touch->getLocation();
};

void PlayerCloser::onTouchEnded(const Touch * touch, Event *unused_event) 
{
	if (delayTimer >= 2.0f)
	{
		if (rightRobot->isMove||leftRobot->isMove)
		{
			isRobotMoving = true;
			delayTimer = 0;
		}
	}
	else 
	{
		isRobotMoving = false;
	}
};

