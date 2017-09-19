#include "EndingCharacterAnimation.h"
#include <cmath>

using namespace cocos2d;
using namespace std;

bool EndingCharacterAnimation::init(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay, bool walk, bool smiling)
{
	if (!Node::init()) return false;

	// standアニメーションのチップ数
	int standChip = 2;

	_chipSize = chipSize;
	vector<SpriteFrame*> bodySp;	// 切り取ったチップを一時的に格納
	vector<SpriteFrame*> ponSp;		// 切り取ったチップを一時的に格納
	vector<SpriteFrame*> faceSp;	// 切り取ったチップを一時的に格納
	Sprite* body = Sprite::create(bodyPath);	// 画像読み込み
	Sprite* pon = Sprite::create(ponPath);	// ポン読み込み
	Sprite* face = Sprite::create(facePath);	// 顔読み込み
	_bodySp = Sprite::create();			// キャラクタースプライト作成
	_ponSp = Sprite::create();			// ポンスプライト作成
	_faceSp = Sprite::create();			// 顔スプライト作成
	this->addChild(_bodySp);
	this->addChild(_ponSp);
	this->addChild(_faceSp);
	_animationChache = AnimationCache::sharedAnimationCache();		// アニメーションキャッシュに溜めることで読み込み減らす

	int i = 0;
	int width = body->getContentSize().width / chipSize.width;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);
			bodySp.push_back(SpriteFrame::createWithTexture(body->getTexture(), rect));
			ponSp.push_back(SpriteFrame::createWithTexture(pon->getTexture(), rect));
			faceSp.push_back(SpriteFrame::createWithTexture(face->getTexture(), rect));
		}
	}

	//-----------------------------------------------------------------------------------------
	// 移動用アニメーション
	//-----------------------------------------------------------------------------------------
	// アニメーション作成
	Animation* walkFront = Animation::create();
	Animation* walkBack = Animation::create();
	Animation* walkLeft = Animation::create();
	Animation* walkRight = Animation::create();

	Animation* ponWalkFront = Animation::create();
	Animation* ponWalkBack = Animation::create();
	Animation* ponWalkLeft = Animation::create();
	Animation* ponWalkRight = Animation::create();

	Animation* normalWalkFB = Animation::create();
	Animation* normalWalkLR = Animation::create();
	Animation* smileWalkFB = Animation::create();
	Animation* smileWalkLR = Animation::create();

	// チップを振り分け
	for (int i = standChip; i < width; i++)	// 移動用割り振り
	{
		walkFront->addSpriteFrame(bodySp[i]);
		walkBack->addSpriteFrame(bodySp[width + i]);
		walkLeft->addSpriteFrame(bodySp[2 * width + i]);
		walkRight->addSpriteFrame(bodySp[3 * width + i]);

		ponWalkFront->addSpriteFrame(ponSp[i]);
		ponWalkBack->addSpriteFrame(ponSp[width + i]);
		ponWalkLeft->addSpriteFrame(ponSp[2 * width + i]);
		ponWalkRight->addSpriteFrame(ponSp[3 * width + i]);

		normalWalkFB->addSpriteFrame(faceSp[i]);
		normalWalkLR->addSpriteFrame(faceSp[width + i]);
		smileWalkFB->addSpriteFrame(faceSp[2 * width + i]);
		smileWalkLR->addSpriteFrame(faceSp[3 * width + i]);
	}

	// ディレイ設定
	walkFront->setDelayPerUnit(delay);
	walkBack->setDelayPerUnit(delay);
	walkLeft->setDelayPerUnit(delay);
	walkRight->setDelayPerUnit(delay);

	ponWalkFront->setDelayPerUnit(delay);
	ponWalkBack->setDelayPerUnit(delay);
	ponWalkLeft->setDelayPerUnit(delay);
	ponWalkRight->setDelayPerUnit(delay);
	
	normalWalkFB->setDelayPerUnit(delay);
	normalWalkLR->setDelayPerUnit(delay);
	smileWalkFB->setDelayPerUnit(delay);
	smileWalkLR->setDelayPerUnit(delay);

	// キャッシュに溜める
	_animationChache->addAnimation(walkFront, "WALK_F");
	_animationChache->addAnimation(walkBack, "WALK_B");
	_animationChache->addAnimation(walkLeft, "WALK_L");
	_animationChache->addAnimation(walkRight, "WALK_R");

	_animationChache->addAnimation(ponWalkFront, "P_WALK_F");
	_animationChache->addAnimation(ponWalkBack, "P_WALK_B");
	_animationChache->addAnimation(ponWalkLeft, "P_WALK_L");
	_animationChache->addAnimation(ponWalkRight, "P_WALK_R");

	_animationChache->addAnimation(normalWalkFB, "N_WALK_FB");
	_animationChache->addAnimation(normalWalkLR, "N_WALK_LR");
	_animationChache->addAnimation(smileWalkFB, "S_WALK_FB");
	_animationChache->addAnimation(smileWalkLR, "S_WALK_LR");

	//-----------------------------------------------------------------------------------------
	// ストップ用アニメーション
	//-----------------------------------------------------------------------------------------
	// アニメーション作成
	Animation* standFront = Animation::create();
	Animation* standBack = Animation::create();
	Animation* standLeft = Animation::create();
	Animation* standRight = Animation::create();

	Animation* ponStandFront = Animation::create();
	Animation* ponStandBack = Animation::create();
	Animation* ponStandLeft = Animation::create();
	Animation* ponStandRight = Animation::create();

	Animation* normalStandFB = Animation::create();
	Animation* normalStandLR = Animation::create();
	Animation* smileStandFB = Animation::create();
	Animation* smileStandLR = Animation::create();

	// チップ振り分け

	for (int i = 0; i < standChip; i++)
	{
		standFront->addSpriteFrame(bodySp[i]);
		standBack->addSpriteFrame(bodySp[width + i]);
		standLeft->addSpriteFrame(bodySp[2 * width + i]);
		standRight->addSpriteFrame(bodySp[3 * width + i]);

		ponStandFront->addSpriteFrame(ponSp[i]);
		ponStandBack->addSpriteFrame(ponSp[width + i]);
		ponStandLeft->addSpriteFrame(ponSp[2 * width + i]);
		ponStandRight->addSpriteFrame(ponSp[3 * width + i]);

		normalStandFB->addSpriteFrame(faceSp[i]);
		normalStandLR->addSpriteFrame(faceSp[width + i]);
		smileStandFB->addSpriteFrame(faceSp[2 * width + i]);
		smileStandLR->addSpriteFrame(faceSp[3 * width + i]);
	}	

	// ディレイ設定
	standFront->setDelayPerUnit(delay);
	standBack->setDelayPerUnit(delay);
	standLeft->setDelayPerUnit(delay);
	standRight->setDelayPerUnit(delay);

	ponStandFront->setDelayPerUnit(delay);
	ponStandBack->setDelayPerUnit(delay);
	ponStandLeft->setDelayPerUnit(delay);
	ponStandRight->setDelayPerUnit(delay);

	normalStandFB->setDelayPerUnit(delay);
	normalStandLR->setDelayPerUnit(delay);
	smileStandFB->setDelayPerUnit(delay);
	smileStandLR->setDelayPerUnit(delay);

	// キャッシュに溜める
	_animationChache->addAnimation(standFront, "STAND_F");
	_animationChache->addAnimation(standBack, "STAND_B");
	_animationChache->addAnimation(standLeft, "STAND_L");
	_animationChache->addAnimation(standRight, "STAND_R");

	_animationChache->addAnimation(ponStandFront, "P_STAND_F");
	_animationChache->addAnimation(ponStandBack, "P_STAND_B");
	_animationChache->addAnimation(ponStandLeft, "P_STAND_L");
	_animationChache->addAnimation(ponStandRight, "P_STAND_R");

	_animationChache->addAnimation(normalStandFB, "N_STAND_FB");
	_animationChache->addAnimation(normalStandLR, "N_STAND_LR");
	_animationChache->addAnimation(smileStandFB, "S_STAND_FB");
	_animationChache->addAnimation(smileStandLR, "S_STAND_LR");

	_dir = eDIR::FRONT;

	if (walk) _state = eENDSTATE::WALK;
	else _state = eENDSTATE::STAND;

	if (smiling) _face = eENDFACE::SMILE;
	else _face = eENDFACE::NORMAL;

	changeAnimation();

	return true;
}

//EndingCharacterAnimation* EndingCharacterAnimation::create(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay)
//{
//	EndingCharacterAnimation* pRet = new EndingCharacterAnimation();
//	if (pRet && pRet->init(bodyPath, ponPath, facePath, chipSize, delay, true))
//	{
//		pRet->autorelease();
//		pRet->_walkingAnim = true;
//		return pRet;
//	}
//	else
//	{
//		delete pRet;
//		pRet = NULL;
//		return NULL;
//	}
//}

EndingCharacterAnimation* EndingCharacterAnimation::createInStand(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay, bool smiling)
{
	EndingCharacterAnimation* pRet = new EndingCharacterAnimation();
	if (pRet && pRet->init(bodyPath, ponPath, facePath, chipSize, delay, false, smiling))
	{
		pRet->autorelease();
		pRet->_state = eENDSTATE::STAND;
		if (smiling) pRet->_face = eENDFACE::SMILE;
		else pRet->_face = eENDFACE::NORMAL;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

EndingCharacterAnimation* EndingCharacterAnimation::createInWalk(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay, bool smiling)
{
	EndingCharacterAnimation* pRet = new EndingCharacterAnimation();
	if (pRet && pRet->init(bodyPath, ponPath, facePath, chipSize, delay, true, smiling))
	{
		pRet->autorelease();
		pRet->_state = eENDSTATE::WALK;
		if (smiling) pRet->_face = eENDFACE::SMILE;
		else pRet->_face = eENDFACE::NORMAL;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void EndingCharacterAnimation::setShadow(std::string shadowPath)
{
	_shadowSp = Sprite::create(shadowPath);
	_shadowSp->setPosition(0.0f, _chipSize.height*-0.47f);
	this->addChild(_shadowSp, -1);
}

void EndingCharacterAnimation::setShadow(SpriteFrame* shadowSp)
{
	_shadowSp = Sprite::createWithSpriteFrame(shadowSp);
	_shadowSp->setPosition(0.0f, _chipSize.height*-0.47f);
	this->addChild(_shadowSp, -1);
}

void EndingCharacterAnimation::changeAnimation()
{
	_bodySp->stopAllActions();
	_ponSp->stopAllActions();
	
	Animation* bodyAnim;
	Animation* ponAnim;

	switch (_state)
	{
	case eENDSTATE::STAND:
		switch (_dir)
		{
		case eDIR::FRONT:
			bodyAnim = _animationChache->animationByName("STAND_F");
			ponAnim = _animationChache->animationByName("P_STAND_F");
			break;
		case eDIR::BACK:
			bodyAnim = _animationChache->animationByName("STAND_B");
			ponAnim = _animationChache->animationByName("P_STAND_B");
			break;
		case eDIR::LEFT:
			bodyAnim = _animationChache->animationByName("STAND_L");
			ponAnim = _animationChache->animationByName("P_STAND_L");
			break;
		case eDIR::RIGHT:
			bodyAnim = _animationChache->animationByName("STAND_R");
			ponAnim = _animationChache->animationByName("P_STAND_R");
			break;
		default:
			break;
		}
		break;
	case eENDSTATE::WALK:
		switch (_dir)
		{
		case eDIR::FRONT:
			bodyAnim = _animationChache->animationByName("WALK_F");
			ponAnim = _animationChache->animationByName("P_WALK_F");
			break;
		case eDIR::BACK:
			bodyAnim = _animationChache->animationByName("WALK_B");
			ponAnim = _animationChache->animationByName("P_WALK_B");
			break;
		case eDIR::LEFT:
			bodyAnim = _animationChache->animationByName("WALK_L");
			ponAnim = _animationChache->animationByName("P_WALK_L");
			break;
		case eDIR::RIGHT:
			bodyAnim = _animationChache->animationByName("WALK_R");
			ponAnim = _animationChache->animationByName("P_WALK_R");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	auto repeatB = RepeatForever::create(Animate::create(bodyAnim));
	auto repeatP = RepeatForever::create(Animate::create(ponAnim));
	_bodySp->runAction(repeatB);
	_ponSp->runAction(repeatP);

	changeFaceAnimation();
}

void EndingCharacterAnimation::changeAnimation(eDIR dirName)
{
	if (dirName == _dir) return;
	_dir = dirName;
	changeAnimation();
}

void EndingCharacterAnimation::changeAnimation(Vec2 dir)
{
	if (abs(dir.x) > abs(dir.y))
	{
		if (dir.x > 0.0f)
		{
			// 右
			changeAnimation(eDIR::RIGHT);
		}
		else
		{
			// 左
			changeAnimation(eDIR::LEFT);
		}
	}
	else
	{
		if (dir.y > 0.0f)
		{
			// 後ろ
			changeAnimation(eDIR::BACK);
		}
		else
		{
			// 前
			changeAnimation(eDIR::FRONT);
		}
	}
}

void EndingCharacterAnimation::changeAnimation(eENDSTATE state)
{
	if (_state == state) return;
	_state = state;
	changeAnimation();
}

void EndingCharacterAnimation::changeAnimation(eENDFACE face)
{
	if (_face == face) return;
	_face = face;
	changeAnimation();
}

void EndingCharacterAnimation::changeDir(eDIR dirName)
{
	if (_dir == dirName) return;
	_dir = dirName;
}

void EndingCharacterAnimation::changeState(eENDSTATE state)
{
	if (_state == state) return;
	_state = state;
}

void EndingCharacterAnimation::changeFace(eENDFACE face)
{
	if (_face == face) return;
	_face = face;
}

void EndingCharacterAnimation::changeFaceAnimation()
{
	_faceSp->stopAllActions();
	Animation* anim;
	switch (_state)
	{
	case eENDSTATE::STAND:
		switch (_dir)
		{
		case eDIR::FRONT:
			switch (_face)
			{
			case eENDFACE::NORMAL:
				anim = _animationChache->animationByName("N_STAND_FB");
				break;
			case eENDFACE::SMILE:
				anim = _animationChache->animationByName("S_STAND_FB");
				break;
			default:
				break;
			}
			break;
		case eDIR::BACK:
			switch (_face)
			{
			case eENDFACE::NORMAL:
				anim = NULL;
				break;
			case eENDFACE::SMILE:
				anim = NULL;
				break;
			default:
				break;
			}
			break;
		case eDIR::LEFT:
			setFlipX(false, _faceSp);
			switch (_face)
			{
			case eENDFACE::NORMAL:
				anim = _animationChache->animationByName("N_STAND_LR");
				break;
			case eENDFACE::SMILE:
				anim = _animationChache->animationByName("S_STAND_LR");
				break;
			default:
				break;
			}
			break;
		case eDIR::RIGHT:
			setFlipX(true, _faceSp);
			switch (_face)
			{
			case eENDFACE::NORMAL:
				anim = _animationChache->animationByName("N_STAND_LR");
				break;
			case eENDFACE::SMILE:
				anim = _animationChache->animationByName("S_STAND_LR");
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case eENDSTATE::WALK:
		switch (_dir)
		{
		case eDIR::FRONT:
			setFlipX(false, _faceSp);
			switch (_face)
			{
			case eENDFACE::NORMAL:
				anim = _animationChache->animationByName("N_WALK_FB");
				break;
			case eENDFACE::SMILE:
				anim = _animationChache->animationByName("S_WALK_FB");
				break;
			default:
				break;
			}
			break;
		case eDIR::BACK:
			setFlipX(false, _faceSp);
			switch (_face)
			{
			case eENDFACE::NORMAL:
				anim = NULL;
				break;
			case eENDFACE::SMILE:
				anim = NULL;
				break;
			default:
				break;
			}
			break;
		case eDIR::LEFT:
			setFlipX(false, _faceSp);
			switch (_face)
			{
			case eENDFACE::NORMAL:
				anim = _animationChache->animationByName("N_WALK_LR");
				break;
			case eENDFACE::SMILE:
				anim = _animationChache->animationByName("S_WALK_LR");
				break;
			default:
				break;
			}
			break;
		case eDIR::RIGHT:
			setFlipX(true, _faceSp);
			switch (_face)
			{
			case eENDFACE::NORMAL:
				anim = _animationChache->animationByName("N_WALK_LR");
				break;
			case eENDFACE::SMILE:
				anim = _animationChache->animationByName("S_WALK_LR");
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (anim != NULL)
	{
		auto repeat = RepeatForever::create(Animate::create(anim));
		_faceSp->runAction(repeat);
	}
}

void EndingCharacterAnimation::changeFaceAnimation(eENDFACE face)
{
	if (_face == face) return;
	_face = face;
	changeFaceAnimation();
}

void EndingCharacterAnimation::stopAnimations()
{
	_bodySp->stopAllActions();
	_ponSp->stopAllActions();
	_faceSp->stopAllActions();
}

void EndingCharacterAnimation::setFlipX(bool is)
{
	if (_isFliped == is) return;
	this->setRotation3D(Vec3(0, 180, 0));
}

void EndingCharacterAnimation::setFlipY(bool is)
{
	if (_isFliped == is) return;
	this->setRotation3D(Vec3(180, 0, 0));
}

void EndingCharacterAnimation::setFlipX(bool is, Node* obj)
{
	if (is) obj->setRotation3D(Vec3(0, 180, 0));
	else obj->setRotation3D(Vec3(0, 0, 0));
}

void EndingCharacterAnimation::setFlipY(bool is, Node* obj)
{
	if (is) obj->setRotation3D(Vec3(180, 0, 0));
	else obj->setRotation3D(Vec3(0, 0, 0));
}

Size EndingCharacterAnimation::getSpriteSize()
{
	return _chipSize;
}

void EndingCharacterAnimation::setDelay(float delayTime)
{
	_animationChache->animationByName("STAND_F")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STAND_B")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STAND_L")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STAND_R")->setDelayPerUnit(delayTime);

	_animationChache->animationByName("P_STAND_F")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_STAND_B")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_STAND_L")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_STAND_R")->setDelayPerUnit(delayTime);

	_animationChache->animationByName("N_STAND_FB")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("N_STAND_LR")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("S_STAND_FB")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("S_STAND_LR")->setDelayPerUnit(delayTime);

	_animationChache->animationByName("WALK_F")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("WALK_B")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("WALK_L")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("WALK_R")->setDelayPerUnit(delayTime);

	_animationChache->animationByName("P_WALK_F")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_WALK_B")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_WALK_L")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("P_WALK_R")->setDelayPerUnit(delayTime);

	_animationChache->animationByName("N_WALK_FB")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("N_WALK_LR")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("S_WALK_FB")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("S_WALK_LR")->setDelayPerUnit(delayTime);

	changeAnimation();
}

Sprite* EndingCharacterAnimation::getBody()
{
	return _bodySp;
}

Sprite* EndingCharacterAnimation::getPon()
{
	return _ponSp;
}

Sprite* EndingCharacterAnimation::getFace()
{
	return _faceSp;
}