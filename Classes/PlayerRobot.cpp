#include "PlayerRobot.h"

PlayerRobot* PlayerRobot::create(Vec2 pos,Color4F col)
{
	PlayerRobot *pRet = new PlayerRobot();
	if (pRet && pRet->init(pos,col))
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

bool PlayerRobot::init(Vec2 pos,Color4F col)
{
	if (!Node::init())return false;

	SimpleAudioEngine::getInstance()->preloadEffect("Sounds/move_4.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Sounds/PlayerGoal.mp3");

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(PlayerRobot::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerRobot::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerRobot::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	setSpeed(2.73f);
	setGameSpeed(1.0f);
	setMoveRange(70.0f);
	setDoubtDgree(150.0f);
	setObjectRange(70.0f);
	checkTime = 120.0f;

	initWithFileCenter("Character/GameAnim_Body.png", "Character/GameAnim_Head.png",Size(210, 210),0.3f);
	mySprite->getSp()->setAnchorPoint(Vec2(0.5f, 0.34f));
	mySprite->getPon()->setAnchorPoint(Vec2(0.5f, 0.34f));
	mySprite->getPon()->setColor(Color3B(col.r*255.0f, col.g*255.0f, col.b*255.0f));
	mySprite->stopAnimation();

	messageSp = Sprite::create("Game/Player/Stop.png");
	messageSp->setPosition(Vec2(0, myPosition.y + 50));
	messageSp->setVisible(false);
	addChild(messageSp,25);
	
	startPosition = pos;
	endPosition = pos + Vec2(1, 0);
	initialize(pos, DIR_DEGREE::DIR_RIGHT);

	lastTargetPosition = targetPosition;

	angleNum = 0;
	isStandby = false;
	isNext = false;
	isMove = false;
	setState(STATUS::STAND);

	goalPa = CutParticle::create("Game/Player/Goal.png",1,2, col);
	addChild(goalPa,5);

	moveRangeSp = DrawNode::create();
	addChild(moveRangeSp);
	moveRangeSp->drawCircle(Vec2(0, 0), moveRange, 0, 360, false, Color4F::GRAY);

	return true;
};

void PlayerRobot::plusAction()
{
	//log("type=%d", (int)myState);
		switch (myState)
		{
		case STATUS::STAND:
			if (isNext)
			{
				nextPosition();
			}
			break;
		case STATUS::MOVE:
			if (onCollision(goal))findPosition();
			break;
		case STATUS::STOP:
			isNext = true;
			break;
		case STATUS::FIND:
			break;
		default:
			break;
		}
		//mySprite->setScale((moveTimer/checkTime)+0.5f);
};

//角度の保存
void PlayerRobot::setAngle(Vec2 from, Vec2 to) 
{
	//cosθの値
	float seta = acos(dot(from,to)/(length(from)*length(to)));
	seta = ragToDeg(seta);
	//右か左か
	if (cross(from, to) < 0) {
	seta = -seta;
	};
	angles.push_back(seta);
};

//歩き始める
void PlayerRobot::moveStart() 
{
	if (myState == STATUS::FIND)return;
	if (angles.size() <= 0)return;
	isMove = true;
	nextPosition();
};

//行くべきところの設定
void PlayerRobot::nextPosition()
{
	isNext = false;
	if (angleNum< angles.size())
	{
		SimpleAudioEngine::getInstance()->playEffect("Sounds/move_4.mp3");
		lastTargetPosition = getDirectionDegree(Vec2(1, 0), angles.at(angleNum), doubtDegree) + myPosition;
		targetPosition = lastTargetPosition;
		angleNum++;
	}
	else
	{
		//次に向かう場所がない場合
		stopPosition();
	}
};

//立ち止まった時
void PlayerRobot::stopPosition()
{
	moveRangeSp->clear();
	angles.clear();
	
	isMove = false;
	isStandby= false;
	angleNum = 0;
	stopAnimation();
};

//ゴールを見つけたとき
void PlayerRobot::findPosition() 
{
	moveRangeSp->clear();
	angles.clear();

	isMove = false;
	isStandby = true;
	angleNum = 0;
	findAnimation();
	SimpleAudioEngine::getInstance()->playEffect("Sounds/PlayerGoal.mp3");
	setState(STATUS::FIND);
};

//止まった時のアニメーション
void PlayerRobot::stopAnimation() 
{
	messageSp->setVisible(true);

	ScaleTo* scaleIn = ScaleTo::create(0.5f, 2);
	RotateTo* rotateIn = RotateTo::create(0.5f, 15);
	Spawn* spawnIn = Spawn::createWithTwoActions(scaleIn, rotateIn);
	ScaleTo* scaleOut = ScaleTo::create(0.5f, 1);
	RotateTo* rotateOut = RotateTo::create(0.5f, 0);
	Spawn* spawnOut = Spawn::createWithTwoActions(scaleOut, rotateOut);

	messageSp->runAction(Sequence::create(spawnIn, spawnOut, nullptr));
};

void PlayerRobot::findAnimation() 
{
	goalPa->setLine(Vec2(0,0),Vec2(0,0));
	goalPa->startParticle();
};

//プレイヤーの操作が異なるので仮想化
bool PlayerRobot::onTouchBegan(const Touch * touch, Event *unused_event)
{
	if (isMove)return false;
	if (myState == STATUS::FIND)return false;

	if (myState == STATUS::STAND) {
		endPosition = myPosition + Vec2(1, 0);
		if (onMoveRange(touch->getLocation()))
		{
			isMoveWait = true;
			isStandby = false;
			angles.clear();
			endPosition = myPosition + Vec2(1, 0);
		}
		else
		{
			isMoveWait = false;
		}
	}
	return true;
};

void PlayerRobot::onTouchMoved(const Touch * touch, Event *unused_event)
{
	setGameSpeed(1.5f);
	if (isMove)return;
	if (myState == STATUS::FIND)return;

	Vec2 touchPosition = touch->getLocation();
	Vec2 stepPosition = myPosition;

	touchPosition = touch->getLocation();
	//画面外に出たときの処理
	if (touch->getLocation().x > designResolutionSize.width)
		touchPosition.x = designResolutionSize.width;
	if (touch->getLocation().x < 0)
		touchPosition.x = 0;
	if (touch->getLocation().y > designResolutionSize.height)
		touchPosition.y = designResolutionSize.height;
	if (touch->getLocation().y < 0)
		touchPosition.y = 0;
	//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

	//タッチしたときにキャラを触っているなら軌道の設定を始める
	if (isMoveWait) {
		//指定した歩数まで
		if (angles.size() < MOVE_MAX) 
		{
			//高速で動かされたときに離れるので等間隔にするためwhile
			while (length(endPosition - touchPosition) >= doubtDegree)
			{
				Vec2 a = Vec2(1, 0);
				Vec2 b = touchPosition - endPosition;
				stepPosition = endPosition;
				endPosition = normalize(touchPosition - endPosition)*doubtDegree + endPosition;
				//軌道の保存
				setAngle(a, b);
				//音
			}
		}
	}
};

void PlayerRobot::onTouchEnded(const Touch * touch, Event *unused_event)
{
	setGameSpeed(1.0f);
	//歩いているなら無効にする
	if(isMove)return;
	if (myState == STATUS::FIND)return;

	//歩数の確定
	if (angles.size() > 0)
	{
		isStandby = true;
	}
	else {
		isStandby = false;
	}
	isMoveWait = false;
};

