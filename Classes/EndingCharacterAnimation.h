#ifndef _EndingCharacterAnimation_h_
#define _EndingCharacterAnimation_h_

#include "cocos2d.h"
#include "CharacterAnimation.h"

enum class eDIR
{
	FRONT = 0,
	BACK,
	LEFT,
	RIGHT
};

enum class eENDSTATE
{
	STAND,
	WALK
};

enum class eENDFACE
{
	NORMAL,
	SMILE
};


/*

〇〇●●　前
〇〇●●　後
〇〇●●　左
〇〇●●　右

〇　待機スプライト　2枚
●　移動アニメーション　2枚

*/


class EndingCharacterAnimation : public cocos2d::Node
{
public:
	virtual bool init(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay, bool walk, bool smiling = false);
	//static EndingCharacterAnimation* create(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay = 0.5f);
	static EndingCharacterAnimation* createInStand(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay = 0.5f, bool smiling = false);
	static EndingCharacterAnimation* createInWalk(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay = 0.5f, bool smiling = false);

	void changeAnimation(eDIR dirName);			// アニメーション切り替え
	void changeAnimation(cocos2d::Vec2 dir);	// アニメーションの向きから画像切り替え
	void changeAnimation(eENDSTATE state);
	void changeAnimation(eENDFACE face);
	void changeDir(eDIR dirName);
	void changeState(eENDSTATE state);
	void changeFace(eENDFACE face);
	
	void changeFaceAnimation(eENDFACE face);

	void stopAnimations();				// アニメーション自体を停止
	cocos2d::Sprite* getBody();			// クラス内のスプライトを取得(オススメしない)
	cocos2d::Sprite* getPon();
	cocos2d::Sprite* getFace();
	void setShadow(std::string shadowPath);
	void setShadow(cocos2d::SpriteFrame* shadowSp);

	void setDelay(float delayTime);		// スプライトの切り替わる早さを指定
	//float getDelay();					// スプライトの切り替わる早さを取得

	//void setDir(cocos2d::Vec2 dir);	// アニメーションの向きを変更
	//void setDir(eDIR dirName);		// アニメーションの向きを変更(enum型)

	cocos2d::Size getSpriteSize();
	void setFlipX(bool is);
	void setFlipY(bool is);

private:
	cocos2d::Sprite* _bodySp;
	cocos2d::Sprite* _ponSp;
	cocos2d::Sprite* _faceSp;
	cocos2d::Sprite* _shadowSp;
	eDIR _dir;
	eENDSTATE _state;
	eENDFACE _face;
	cocos2d::Size _chipSize;
	bool _isFliped = false;

	void setFlipX(bool is, cocos2d::Node* obj);
	void setFlipY(bool is, cocos2d::Node* obj);

	void changeAnimation();
	void changeFaceAnimation();

	cocos2d::AnimationCache* _animationChache;
};

#endif // !_EndingCharacterAnimation_h_
