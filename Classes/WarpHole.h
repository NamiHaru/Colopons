#ifndef __WARPHOLE_H__
#define __WARPHOLE_H__

#include "AllTags.h"
#include "ObjectBase.h"
#include "PlayerCloser.h"

using namespace std;

//�Ώۂ�����q�b�g���Ƀp�[�g�i�[�̃z�[���Ƀ��[�v��������
//���[�v��̃z�[���̓L�����N�^�[�������܂Ŏ��񃏁[�v��������

//���[�v�z�[���P��
class Hole :public ObjectBase 
{
public:
	static Hole* create(Vec2 spawnPos);
	//�����ݒ�
	virtual bool init(Vec2 spawnPos);
	//�X�V
	virtual void update(float delta);

	//�ω��A�j���[�V����
	void playAnimation(bool startOrEnd);

	Sprite* mySprite;
	bool isHit;
};

//�΂ɂȂ郏�[�v�z�[���̊Ǘ���
class WarpHole :public Node
{
public:
	static WarpHole* create(Vec2 w1, Vec2 w2,PlayerCloser* target);
	bool init(Vec2 w1, Vec2 w2,PlayerCloser* target);
	void update(float delta);
	
	void setTargetPlayers(PlayerCloser* p);
	//�Ώۂ����g�ɏՓ˂����炻�̑Ώۂ��u�Ԉړ�������
	//�����葱���Ă���ꍇ�͖����ɂȂ�
	void objectWarp(Character* target, Vec2& partner);
	void warpAnimation(Hole*start,Hole* end);
	bool onCollisionPlayers();


	PlayerCloser* player;//�ΏۂƂ���v���C���[
	Hole *warp1, *warp2;//�Ǘ����郏�[�v�z�[��
	bool inWarpMiddle;//���[�v���Ă���Œ���

};

#endif // !__WARPHOLE_H__
