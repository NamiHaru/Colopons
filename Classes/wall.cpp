#include "Wall.h"

Wall* Wall::create(Rect rect, Color4F fillColor, Color4F segmentColor)
{
	Wall *pRet = new Wall();
	if (pRet && pRet->init(rect,fillColor,segmentColor))
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

Wall* Wall::create(Vec2* vecs,int count, Color4F fillColor = Color4F(0, 0, 0, 1.0f), Color4F segmentColor = Color4F(255, 255, 255, 1.0f)) 
{
	Wall *pRet = new Wall();
	if (pRet && pRet->init(vecs,count, fillColor, segmentColor))
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

bool Wall::init(Rect rect, Color4F fillColor, Color4F segmentColor)
{
	if (!Node::init())return false;

	SimpleAudioEngine::getInstance()->preloadEffect("Sounds/walldust.mp3");

	particle = CutParticle::create("Game/Wall/Slash.png",20,1);
	addChild(particle,60);

	Sprite* sp = Sprite::create();

	points[0] = Vec2(rect.getMinX(), rect.getMinY());//左下
	points[1] = Vec2(rect.getMaxX(), rect.getMinY());//右下
	points[2] = Vec2(rect.getMaxX(), rect.getMaxY());//右上
	points[3] = Vec2(rect.getMinX(), rect.getMaxY());//左上
	points[4] = Vec2(0, 0);//5角形になった時用
	points[5] = Vec2(0, 0);//分割時に必要になる

	myWall = DrawNode::create();
	myWall->setPosition(myWall->getPosition() - getPosition());

	debug = DrawNode::create();
	debug->setPosition(-getPosition());
	addChild(debug, 51);

	//頂点座標設定
	std::vector<Vec2>vecs;
	vecs.push_back(points[0]);
	vecs.push_back(points[1]);
	vecs.push_back(points[2]);
	vecs.push_back(points[3]);

	myWall->drawPolygon(&vecs[0], 4, fillColor, 1, segmentColor);

	myWall->setPosition(-getPosition());

	addChild(myWall);

	clipp = ClippingNode::create();
	clipp->setStencil(myWall);
	clipp->addChild(sp);
	addChild(clipp);

	isCuted = false;
	segmentCount = 4;
	scheduleUpdate();

	return true;
};

bool Wall::init(Vec2* vecs, int count,Color4F fillColor, Color4F segmentColor) 
{
	if (!Node::init())return false;


	particle = CutParticle::create("Game/Wall/Slash.png",20,1);
	addChild(particle, 60);

	for (int i = 0; i < count; i++) 
	{
		points[i] = vecs[i];
	}

	myWall = DrawNode::create();
	myWall->setPosition(myWall->getPosition() - getPosition());

	debug = DrawNode::create();
	debug->setPosition(-getPosition());
	addChild(debug, 51);

	myWall->drawPolygon(&vecs[0], 4, Color4F::WHITE, 1, Color4F::BLACK);
	//myWall->drawSegment(points[0], points[2], 5, Color4F::WHITE);
	//myWall->drawSegment(points[1], points[3], 5, Color4F::WHITE); 


	addChild(myWall);

	clippSprite = Sprite::create("Game/Wall/wallMask.png");
	clippSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	//addChild(clippSprite);

	clipp = ClippingNode::create();
	clipp->setStencil(myWall);
	clipp->addChild(clippSprite);
	addChild(clipp);

	isCuted = false;
	segmentCount = 4;
	scheduleUpdate();

	int a[] = { 0,1,2,3,-1 };
	log("area=%0.2f",sumArea(vecs, a));

	return true;
};


void Wall::update(float delta)
{
	if (*playerCut)
	{
		particle->setLine(*fromPos,*toPos);
		callCollision();
	}
	if (cutTimer < 0.5f)cutTimer += 0.01f;//速度変化
	else	cutTimer += 0.005f;
	
	if (cutTimer >= 1.0f)//ループさせる
	{
		cutTimer = 0;
		isCuted = false;
	}
	debug->clear();
	for (int i = 0; i < segmentCount; i++)
	{
			debug->drawSegment(points[i], getOverPoint(points, segmentCount, i + 1), 7, Color4F(sin(cutTimer*M_PI)/2 , sin(cutTimer*M_PI)/2 , sin(cutTimer*M_PI)/2 , 1));
	}
};

//カットした後の色を設定する
void Wall::setCutedColor(Color4F cColor) 
{
	cutedColor = cColor;
};

void Wall::setTargets(Vec2* from, Vec2* to) 
{
	fromPos = from;
	toPos = to;
};

//新しくポイントを設定する
void Wall::setPoint(int number, Vec2 point) 
{
//	points[number] = point;
};

//切り取られるほうのポイントを設定する
void Wall::setDustPoints(Vec2* dust) 
{

};

//衝突判定命令
void Wall::callCollision()
{
	if (segmentCount + 2 >= POINT_SIZE)return;

	Vec2 temp[POINT_SIZE];
	Vec2 pos;
	int count = segmentCount;
	for (int i = 0; i < segmentCount+2; i++) {
		temp[i] = points[i];
	}

	for (int i = 0; i < count; i++)
	{
		//点が当たっているか
		if (checkPoint(&pos,&dustSlope, SEGMENT(*fromPos, *toPos), SEGMENT(temp[i], getOverPoint(temp, count, i + 1))) == 1)
		{
			//点を追加
			i++;
			addPointNum[count - segmentCount] = i;
			addPoint(&pos, temp, i);
			count++;
			if (count ==segmentCount+2)
				break;
		}
	}
	if (count == segmentCount+2)
	{
		for (int i = 0; i < segmentCount+2; i++){
			points[i] = temp[i];
		}
		checkCutArea(points);
	}
};

//from-to間の線とtargetの交点を調べる
int Wall::checkPoint(Vec2* hitPos,float* s0Slope, SEGMENT s0, SEGMENT s1)
{
	//X軸方向のベクトルが0かどうか
	if (s0.to.x == 0.0f || s1.to.x == 0.0f) {
		if (s0.to.x == 0.0f&&s1.to.x == 0.0f)
			return 0;
		//平行

		Vec2 r;
		float t0, t1;
		if (s0.to.x == 0.0f) {
			r.x = s0.from.x;
			r.y = (s1.to.y / s1.to.x)*(r.x - s1.from.x) + s1.from.y;

			t0 = (r.y - s0.from.y) / s0.to.y;		//t=0~1の時は線分s0内
			t1 = (r.x - s1.from.x) / s1.to.x;		//t=0~1の時は線分s1内
		}
		else {
			r.x = s1.from.x;
			r.y = (s0.to.y / s0.to.x)*(r.x - s0.from.x) + s0.from.y;

			t0 = (r.x - s0.from.x) / s0.to.x;		//t=0~1の時は線分s0内
			t1 = (r.y - s1.from.y) / s1.to.y;		//t=0~1の時は線分s1内
		}
		if ((t0<0.0f) || (t0>1.0f) || (t1 < 0.0f) || (t1 > 1.0f))return 0;
		if (hitPos) *hitPos = r;
		return 1;
	}
	else {
		//線分の傾きを求める
		float a0 = s0.to.y / s0.to.x;
		float a1 = s1.to.y / s1.to.x;
	
		//傾きを保存
		if (s0Slope)*s0Slope = a1;
	

		//傾きが同一の場合は平行なので衝突しない
		if ((a0 == a1) || a0 == -a1)return 0;

		//交点のx,y座標を求める
		Vec2 r;
		r.x = (a0*s0.from.x - a1*s1.from.x + s1.from.y - s0.from.y) / (a0 - a1);
		r.y = a0*(r.x - s0.from.x) + s0.from.y;

		//交点が線分内にあるか調べる
		float t0 = (r.x - s0.from.x) / s0.to.x;		//t=0~1の時は線分s0内
		float t1 = (r.x - s1.from.x) / s1.to.x;		//t=0~1の時は線分s1内

		if ((t0<0.0f) || (t0>1.0f) || (t1<0.0f) || (t1>1.0f))return 0;

		//衝突していることを返す
		if (hitPos)*hitPos = r;
		return 1;
	}
};

//検出した点が含まれている線を検出した点を境に分割する
//hitPos=追加する点
//points=追加先の配列
//toNum=追加先の配列に入れたい番号
void Wall::addPoint(Vec2* hitPos, Vec2* points	,int toNum) 
{
	Vec2 point;
	point = *hitPos;
	for (int i =segmentCount+2-1; i > toNum; i--) 
	{
		points[i] = points[i - 1];
	}
	points[toNum] = point;
};

//点の順番の入れ替え
void Wall::swapPoint(Vec2* points, int one, int two) 
{
	Vec2 temp = points[two];
	points[two] = points[one];
	points[one] = temp;
};

//配列の中を先頭から3つずつ取り出した点で面積の合計を返す
float Wall::sumArea(Vec2 points[],int point[]) 
{
	float area = 0;
	for (int i = 0; point[i+2] != -1; i++) 
	{
		area += (
			length(points[point[i]] - points[point[i+1]])+
			length(points[point[i+1]] - points[point[i+2]])+ 
			length(points[point[i+2]] - points[point[i]])
			)/2;
	}
	return area;
};

//角の頂点をなくして、その頂点をつないでいた線同士をつないだ5角形を作る
void Wall::changePentagon(Vec2 *vPoint, int onePoint, int twoPoint)
{
	Vec2* from=vPoint;
	int pointNum;
	//頂点がなくなるので、その前の点とそのあとの点をつなぐ
	if ((onePoint + 1 )% 5 == (twoPoint - 1) % 5) 
	{
		pointNum = (onePoint + 1) % 5;
	}
	//いらない頂点を消す
	for (int i = pointNum; i < 5; i++) 
	{
		vPoint[i] = vPoint[i + 1];
	}
};

//切り取る場所検出
void Wall::checkCutArea(Vec2* points)
{
	Vec2 dustPoints[POINT_SIZE];
	int right[POINT_SIZE], left[POINT_SIZE];
	int rightcount = 0, leftcount = 0;
	float sumRight = 0;
	float sumLeft = 0;
	for (int i = 0; i < segmentCount + 2; i++) {
		if (i != addPointNum[0] && i != addPointNum[1])
			//追加した二つの点でできた線の右側かどうか
			if (cross(points[addPointNum[0]] - points[addPointNum[1]], points[addPointNum[0]] - points[i])>0)
			{
				right[rightcount] = i;
				rightcount++;
			}
			else {
				left[leftcount] = i;
				leftcount++;
			}
	}
	//二度切ろうとするのを防止
	if (rightcount == 0 || leftcount == 0)return;

	//分割線を追加
	right[rightcount++] = addPointNum[0];
	right[rightcount++] = addPointNum[1];
	right[rightcount] = -1;//NULLコード

	left[leftcount++] = addPointNum[0];
	left[leftcount++] = addPointNum[1];
	left[leftcount] = -1;//NULLコード

	//切り取りエフェクト
	cutEffect();

	//面積比を見る
	sumRight = sumArea(points, right);
	log("sumRight=%0.0f", sumArea(points, right));
	sumLeft = sumArea(points, left);
	log("sumLeft=%0.0f", sumArea(points, left));

	if (abs((sumRight-sumLeft))/(sumRight+sumLeft)<=0.002f)
	{
		//log("allCut");
		//大きさがほぼ一緒(クリティカル) 

		copyPoints(points, dustPoints, segmentCount + 2);
		sortPoints(dustPoints, left);
		rebuildingDust(dustPoints, leftcount);

		copyPoints(points, dustPoints, segmentCount + 2);
		sortPoints(dustPoints, right);
		rebuildingDust(dustPoints, rightcount);

		rebuildingArea(points, 1);

		Sprite* sp = Sprite::create("Game/Wall/Critical.png");
		sp->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.7f));
		sp->setColor(Color3B(cutedColor.r*255.0f,cutedColor.g*255.0f,cutedColor.b*255.0f));
		sp->setScale(0);
		addChild(sp);
		ScaleTo* scaleUp = ScaleTo::create(0.5f, 1.0f);
		ScaleTo* scaleDown = ScaleTo::create(0.5f, 0.5);
		FadeOut* fade = FadeOut::create(1.0f);
		Spawn* spawn = Spawn::createWithTwoActions(scaleDown, fade);
		RemoveSelf* self = RemoveSelf::create();
		sp->runAction(Sequence::create(scaleUp,spawn,self,nullptr));
	}
	else if(sumRight> sumLeft)
	{
		//log("right");
		copyPoints(points, dustPoints, segmentCount + 2);
		sortPoints(dustPoints, left);
		
		rebuildingDust(dustPoints, leftcount);
		sortPoints(points, right);
		//構築
		rebuildingArea(points, rightcount);
	}
	else
	{
		//log("left");
		copyPoints(points, dustPoints, segmentCount + 2);
		sortPoints(dustPoints, right);
	
		rebuildingDust(dustPoints, rightcount);
		sortPoints(points, left);
		//構築
		rebuildingArea(points, leftcount);
	}

};

//切り取った後に面積を再構築する
void Wall::rebuildingArea(Vec2 points[], int corner)
{
	//頂点座標設定
	std::vector<Vec2>vecs;
	for (int i = 0; i < corner; i++) {
		vecs.push_back(points[i]);
		log("plus-[%0.0f,%0.0f]", points[i].x, points[i].y);
	}
	myWall->clear();
	myWall->drawPolygon(&vecs[0], corner, Color4F::BLACK, 4, Color4F::WHITE);

	clipp->setStencil(myWall);
	segmentCount = corner;
	log("segment=%d", segmentCount);
};

//切り取った後に面積を再構築する
void Wall::rebuildingDust(Vec2 points[], int corner)
{
	log("dustCorner=%d", corner);

	WallDust* dust = WallDust::create(points, corner, cutedColor);
	addChild(dust);
	//	//頂点座標設定
	//std::vector<Vec2>vecs;
	//for (int i = 0; i < corner; i++) {
	//	vecs.push_back(points[i]);
	//}
	//DrawNode* dDust = DrawNode::create();
	//addChild(dDust);
	//dDust->drawPolygon(&vecs[0], corner, cutedColor, 4, Color4F::WHITE);
	/*
	MoveBy* by = MoveBy::create(1,getDirectionDegree(Vec2(1,0), ragToDeg(dustSlope),100));
	dDust->runAction(by);
	*/
};

//切り取られる演出
void Wall::cutEffect()
{
	SimpleAudioEngine::getInstance()->playEffect("Sounds/walldust.mp3");
	particle->createParticle();
};


//コピーする
void Wall::copyPoints(Vec2* from, Vec2* out, int number) 
{
	for (int i = 0; i<number; i++) {
		out[i] = from[i];
	}
};


//順番を右回りに戻す
void Wall::sortPoints(Vec2* points, int*nums) 
{
	int temp;
	Vec2 pos;

	for (int i = 0; nums[i] != -1; i++) 
		for (int j = i; nums[j] != -1; j++)
		{
			if (nums[i] > nums[j]) 
			{
				//入れ替え
				temp = nums[i];
				nums[i] = nums[j];
				nums[j] = temp;
			}
		}
	for (int i = 0; nums[i] != -1; i++)
	{
		pos = points[i];
		points[i] = points[nums[i]];
		points[nums[i]] = pos;
	}
};


//壁の配列が規定より超えたときに超えた分だけ0から数える
Vec2 Wall::getOverPoint(Vec2 points[],int limit,int num) 
{
	int c=num;
	if (limit == 0)return points[c];

	if (num >= limit)
	{
		c = num%limit;
	}
	return points[c];
};

//選択点と次の点との方向ベクトルを返す
Vec2 Wall::getSegment(int startpoint) 
{
	Vec2 pos;
	pos = getOverPoint(points, segmentCount, startpoint+1)-points[startpoint];
	return pos;
};

