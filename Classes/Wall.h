#ifndef __WALL_H__
#define __WALL_H__

#include "cocos2d.h"
#include "AllTags.h"
#include "CutParticle.h"
#include "WallDust.h"

USING_NS_CC;

#define SQUARE_SIZE 4
#define POINT_SIZE 50

//���ɋ��܂ꂽ�Ƃ��ɖʐς̏��Ȃ��ق������ł����
class Wall :public Node
{
public:
	static Wall* create(Rect rect, Color4F fillColor, Color4F segmentColor);
	bool init(Rect rect, Color4F fillColor, Color4F segmentColor);
	static Wall* create(Vec2* vecs,int count ,Color4F fillColor, Color4F segmentColor);
	bool init(Vec2* vecs,int count, Color4F fillColor, Color4F segmentColor);
	void update(float delta);

	int segmentCount;
	int drawCount;
	float dustSlope;
	float cutTimer;
	Vec2 points[POINT_SIZE];
	bool* playerCut;
	bool isCuted;
	DrawNode* myWall,*debug;
	ClippingNode* clipp;
	Color4F cutedColor;
	//���������
	Vec2 *fromPos,*toPos;
	CutParticle* particle;
	Sprite*clippSprite;

	//------------------------------------------
	//���͂�����g���ĕ�������������
	//�ǉ������ʒu�̔ԍ�
	int addPointNum[2];
	//-----------------------------------------
	//�J�b�g������̐F��ݒ肷��
	void setCutedColor(Color4F cColor);
	
	void setTargets(Vec2* from,Vec2* to);
	//�V�����|�C���g��ݒ肷��
	void setPoint(int number, Vec2 point);
	//�؂�����ق��̃|�C���g��ݒ肷��
	void setDustPoints(Vec2* dust);
	//�Փ˔��薽��
	void callCollision();
	//from-to�Ԃ̐���target�̌�_�𒲂ׂ�
	int checkPoint(Vec2* hitPos, float* s0Slope,SEGMENT s0, SEGMENT s1);
	//���o�����_��ǉ����āA�z��̒��ɓ����
	void addPoint(Vec2* hitPos,Vec2* points,int toNum);
	//�_�̏��Ԃ̓���ւ�
	void swapPoint(Vec2* points,int one,int wto);
	//�z��̒���擪����3�����o�����_�Ŗʐς̍��v��Ԃ�
	float sumArea(Vec2 seg[], int point[]);
	//�p�̒��_���Ȃ����āA���̒��_���Ȃ��ł��������m���Ȃ���5�p�`�����
	void changePentagon(Vec2 *vPoint, int onePoint,int twoPoint);
	//�؂���ꏊ���o
	void checkCutArea(Vec2* seg );
	//�؂�������ɖʐς��č\�z���鎋�o����
	void rebuildingArea(Vec2 seg[], int corner);
	//�؂���ꂽ�ق��̖ʐς��č\�z���ď����Ă���
	void rebuildingDust(Vec2 seg[], int corner);

	//�؂����鉉�o
	void cutEffect();
	//�R�s�[����
	void copyPoints(Vec2* from, Vec2* out, int number);
	//���Ԃ��E���ɖ߂�
	void sortPoints(Vec2* points, int*nums);
	//�ǂ̔z�񂪋K���蒴�����Ƃ��ɒ�����������0���琔����
	Vec2 getOverPoint(Vec2 points[],int limit,int num);
	//�I��_�Ǝ��̓_�Ƃ̕����x�N�g����Ԃ�
	Vec2 getSegment(int startpoint);
};

#endif // !__WALL_H__