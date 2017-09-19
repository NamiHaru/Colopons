#include "MapCreator.h"

MapCreator* MapCreator::create(int num,Color4F col) 
{
	MapCreator *pRet = new MapCreator();
	if (pRet && pRet->init(num,col))
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

bool MapCreator::init(int num,Color4F col) 
{
	if (!Node::init()) 
	{
		return false;
	}

	playerColor = Color4F(col.r/255.0f,col.g / 255.0f,col.b / 255.0f,1.0f);
	
	Wall* aroundWall = Wall::create(
		Rect(designResolutionSize.width*0.05f,designResolutionSize.height*0.05f,
			designResolutionSize.width*0.9f,designResolutionSize.height*0.9f),Color4F(0,0,0,0),Color4F::BLACK);

	walls.pushBack(aroundWall);

openMapFile("stage",num);

	return true;
};

//マップファイル読み込み
void MapCreator::openMapFile(char* name,int num)
{
	String* filename = String::createWithFormat("Stages/%s_%0d.bin", name,num);
	string fileText = FileUtils::getInstance()->getStringFromFile(filename->getCString());
	mapLevel = num;

	loadMap(fileText);
};

//マップ情報管理関数
void MapCreator::loadMap(string mapText) 
{
	for (int i = 0; mapText.size()>i; i++)//データが終わるまで
	{
		switch (mapText[i])
		{
		case 'C'://Character
			log("characterStart");
			analyzePlayer(getAnalyzeData(mapText.substr(i+2,i+D_L_PLAYER),D_L_PLAYER));
			log("characterEnd\n--------------------------------------");
			i += D_L_PLAYER;
			break;
		case '#'://Goal
			log("goalStart");
			analyzeGoal(getAnalyzeData(mapText.substr(i + 1, i + D_L_GOAL), D_L_GOAL));
			i += D_L_GOAL;
			log("goalEnd\n--------------------------------------");
			break;
		case 'W'://Wall
			log("wallStart");
			analyzeWall(getAnalyzeData(mapText.substr(i + 1, i + D_L_WALL), D_L_WALL));
			i += D_L_WALL;
			log("wallEnd\n--------------------------------------");
			break;
		case 'F'://Floor
			log("floorStart");
			//analyzeFloor(getAnalyzeData(mapText.substr(i + 1, mapText.size()-i),D_L_FLOOR));
			i += D_L_FLOOR;
			log("floorend\n--------------------------------------");
			break;
		default:
			//log("default");
			break;
		}
	}
};

void MapCreator::pushObject(Wall*& obj, String* &id)
{
	names.pushBack(id);
	walls.pushBack(obj);
};

void MapCreator::pushObject(Node*& obj, String* &id)
{
	names.pushBack(id);
	floors.pushBack(obj);
};

//マップの配置
void MapCreator::putObject(Character* &obj, Vec2 pos)
{

};

//配置キャラの解析
//主人公21,
//敵12
void MapCreator::analyzePlayer(char* data)
{
	Vec2 oneP, twoP;
	DIR_DEGREE oneR=DIR_DEGREE::DIR_DOWN, twoR=DIR_DEGREE::DIR_DOWN;

			oneP.x = getCharToFloat(data);
			//4バイト単位で座標を管理しているため
			data += 4;
			oneP.y = getCharToFloat(data);
			data += 4;
			twoP.x = getCharToFloat(data);
			data += 4;
			twoP.y = getCharToFloat(data);
	log("human[%f,%f]", oneP.x, oneP.y);
	log("dog[%f,%f]", twoP.x, twoP.y);

	robot = PlayerCloser ::create(oneP, twoP,playerColor);
	log("push-player");

};
void MapCreator::analyzeGoal(char* data)
{
	Vec2 pos;
	int r,g,b;
	r = (getHexToInt(data)*16)+(getHexToInt(data+1));//赤の要素
	data += 2;
	g = (getHexToInt(data)*16)+(getHexToInt(data + 1));//青の要素
	data += 2;
	b = (getHexToInt(data)*16)+(getHexToInt(data + 1));//緑の要素
	data += 2;
	pos.x = getCharToFloat(data);
	data += 4;
	pos.y = getCharToFloat(data);
	goal = Goal::create(pos, Color4F((float)r/255.0f, (float)g/255.0f, (float)b/255.0f,1.0f));
	log("goal[%f,%f]", pos.x, pos.y);
	log("push-enemy");
};
void MapCreator::analyzeWall(char* data)
{
	Rect rect;
	Vec2 vecs[SQUARE_SIZE];
	if (data[0] == 'V')
	{
		data ++;
		for (int i = 0; i < SQUARE_SIZE; i++)
		{
			vecs[i] = Vec2(getCharToFloat(data), getCharToFloat(data + 4));
			data += 8;
		}
		Wall* w = Wall::create(vecs,SQUARE_SIZE, Color4F::BLACK, Color4F::WHITE);
		walls.pushBack(w);
	}
	else//正方形
	{
		data++;
		rect.setRect(getCharToFloat(data), getCharToFloat(data + 4), getCharToFloat(data + 8), getCharToFloat(data + 12));
		Wall* w = Wall::create(rect, Color4F::BLACK, Color4F::WHITE);
		walls.pushBack(w);
	}
	log("push-wall");
};

void MapCreator::analyzeObject(char* data)
{

};

void MapCreator::analyzeFloor(char* data)
{
	int maxX = getCharToInt(data);
	data += 4;
	int maxY = getCharToInt(data);
	log("map=[%d%d]", maxX, maxY);

	//マップチップ取得
	SpriteBatchNode* batch = SpriteBatchNode::create("mapChip.png");
	addChild(batch);
	int chipNum = 3;

	char* mapData = analyzeData;
	//座標分のシフト
	mapData += D_FLOOR_LINE;

	for (int y = 0; y<maxY; y++)
		for (int x = 0; x<maxX; x++)
		{
			//二文字ずつ取得
			//64は画像サイズ。タイリングマップチップ
			Sprite* sp = Sprite::createWithTexture(batch->getTexture(),
				Rect(getHexToInt(mapData++)* TILE_SIZE, getHexToInt(mapData++)*TILE_SIZE,TILE_SIZE,TILE_SIZE),false);
			sp->setPosition(Vec2(chipNum*x*TILE_SIZE+(TILE_SIZE/2),(maxY*TILE_SIZE)-chipNum*y*TILE_SIZE+(TILE_SIZE/2)));
			sp->setScale(chipNum);
			floors.pushBack(sp);
		//	log("map[%d,%d]", x,y);
		}
};

char* MapCreator::getAnalyzeData(string text, int length)
{
	//必ず解析データを初期化する
	for (int i = 0; i < length;i++)
	{
		analyzeData[i] = '\0';
	}
	//なんか16バイトずつで読み込んでるtextくん

	for (int i = 0; i < length&&i<text.size(); i++) 
	{
		analyzeData[i] = text[i];
	};
	//log("%s", analyzeData);
	return analyzeData;
};

float MapCreator::getCharToFloat(char* data,int length) 
{
	if (length >= 16)
	{
		log("error!-sizeover-[16]<length");
		return 0;
	}

	char buf[16];
		for (int j = 0; j < length; j++)
		{
			buf[j] = *data;
			data++;
		}
		buf[length] = '\0';
		log("floatbuf-%s", buf);
		return (float)atof(buf);
};

int MapCreator::getCharToInt(char* data, int length) 
{
	if (length >= 16) 
	{
		log("error!-sizeover-[16]<length");
		return 0;
	}

	char buf[16];
	for (int i = 0; i < length; i++) 
	{
		buf[i] = *data;
		data++;
	};
	buf[length] = '\0';
	//log("intbuf-%s", buf);

	return atoi(buf);
};

//16進数を10進数に戻す
int MapCreator::getHexToInt(char* data,int length)
{
	char tmp = *data;

	if ('0' <= tmp && '9' >= tmp) return (tmp - 0x30);//0x30は'0'の文字コード
	if ('A' <= tmp && 'F' >= tmp) return (tmp + 0x0A - 0x41);//0x41は'A'の文字コード
	if ('a' <= tmp && 'f' >= tmp) return (tmp + 0x0A - 0x61);//0x61は'a'の文字コード

	return 0;
}

//特定の文字を探して、配列内の番号を返す
int MapCreator::getFindCharNumber(char* data,char find)
{
	int num = 0;
	for (int i = 0; data[i] != '\0'; i++)
	{
		if (data[i] == find) 
		{
			num = i;
			log("find[%c]/num[%d]", find,i);
			break;
		}
	}
	return num;
};

DIR_DEGREE MapCreator::getCharToDirction(char* dir) 
{
	char temp = *dir;
	switch (temp)
	{
	case 'E'://EAST
		log("E");
		return DIR_DEGREE::DIR_RIGHT;
		break;
	case 'N'://NORTH
	log("N");
		return DIR_DEGREE::DIR_UP;
		break;
	case 'W'://WEST
		log("W");
		return DIR_DEGREE::DIR_LEFT;
		break;
	case 'S'://SOUTH
		log("S");
		return DIR_DEGREE::DIR_DOWN;
		break;
	default:
		break;
	}
};

//マップ内の衝突関係処理
void MapCreator::checkWall(Character* obj, Vector<Wall*>wall, float range) 
{
	for (int i = 0; i < wall.size(); i++) 
	{
		//同じものを入れることはないようにする
		if (length(obj->myPosition-wall.at(i)->getPosition()) < range)
		{
			obj->setTargetWall(wall.at(i));
			log("check");
		}
	}
};



Layer* MapCreator::printMap()
{
	log("printStart\n--------------------------------------");
	Layer* layer = Layer::create();
	log("Character\n--------------------------------------");
	layer->addChild(robot, 4);
	log("Goal");
	robot->rightRobot->setTarget(goal);
	robot->leftRobot->setTarget(goal);
	layer->addChild(goal, 4);
	goal->setisGoalAddress(&robot->isGoal);
	log("wall");
	log("size=%d\n--------------------------------------", walls.size());
	for (int i = 0; i < walls.size(); i++)
	{
		robot->rightRobot->setTargetWall(walls.at(i));
		robot->leftRobot->setTargetWall(walls.at(i));
		walls.at(i)->setCutedColor(playerColor);
		walls.at(i)->playerCut = &robot->isRobotMoving;
		walls.at(i)->setTargets(&robot->rightRobot->myPosition, &robot->leftRobot->myPosition);
		layer->addChild(walls.at(i), 3);
	}
	log("floor");
	log("size=%d\n--------------------------------------", floors.size());
	for (int i = 0; i < floors.size(); i++)
	{
		layer->addChild(floors.at(i), 0);
	}
	log("createEnd\n--------------------------------------");

	Sprite*sp = Sprite::create();
	sp->setTextureRect(Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
	sp->setPosition(designResolutionSize*0.5f);
	sp->setColor(Color3B::WHITE);
	layer->addChild(sp);

	return layer;
};

//レベルのセット
void MapCreator::setLevel(int level) 
{
	mapLevel = level;
};

int MapCreator::getLevel() 
{
	return mapLevel;
};
