#ifndef INCLUDED_OBJ2D
#define	INCLUDED_OBJ2D

#include <list>
#include "../GameLib/vector.h"
#include "../GameLib/obj2d_data.h"

class OBJ2D;

class MoveAlg
{
public:
    virtual void move(OBJ2D* obj) = 0;  
};


class EraseAlg
{
public:
    virtual void erase(OBJ2D* obj) = 0; 
};

enum obj_type
{
	tNOTHING,
	tPLAYER,
	tENEMY,
	tENEMY2,
	tGROUND,
	tWall,
	tENEMY_SKILL,//���E
    tFIREBALL,
    tBOMB_FIREBALL,
    tBOMB,
	tENEMY_GROUND,
	tENEMY_SKILL2,//�v���C���[��
	tENEMY_SKILL3,//�G��
	tENEMY_SKILL4,//�J
	tSHADOW,
};


class OBJ2D
{
public:
    // �����o�ϐ�
	BOOL                    exist;				// ����
	int                     type;				// �^�C�v
	float                   hp;

	GameLib::Sprite*		data;				// �X�v���C�g�f�[�^
	VECTOR2 				anime;				// �A�j���[�V�����N���X
    VECTOR2                 position;           // �ʒu
	VECTOR2					is3Dposition[4];    // (�l�p)�ʒu

	// �`��p�ϐ�
	VECTOR2					pos;				// �`��ʒu
    VECTOR2                 scale;              // �X�P�[��
	VECTOR2					draw_scale;
	VECTOR2					texPos;				// ���摜�ʒu
	VECTOR2					texSize;			// ���摜�傫��
	VECTOR2					texPivot;			// ��_�̈ʒu
	float					height;
    float                   angle;              // �p�x
    VECTOR4                 color;              // �`��F
	float					distance;			// �`���Y��(1080)�Ƃ̋���
	float					sideMove;
	bool					isDraw3D;			// 3D�̕`��
	float					is3DSize;           // ����
	VECTOR2					is3Dpos[4];			// (�l�p)�`��ʒu

	//�X�V�p
    MoveAlg*                mvAlg;              // �ړ��A���S���Y��
	int						move_pattern;
	int                     state;              // �X�e�[�g
	int                     timer;              // �^�C�}�[

	float                   size;               // ������p�T�C�Y�i���a�j
    float                   velocity;           // ���x
    VECTOR2                 speed;              // �u�Ԃ̈ړ��ʃx�N�g
	int						invincible_timer;	// ���G���	

	OBJ2D*	                judgeFlag[4];          // �����蔻��i�Ώۂ�Ԃ��j
	VECTOR2                 nock_back;			// �m�b�N�o�b�N�ړ���

    OBJ2D*                  P;                  //(�Ώۂ�Ԃ�)
    bool                    screen_drow;        //(�J�����Ɋ����Ȃ�)

    BYTE                    pad[1];             // 1�o�C�g�̋�
public:

    OBJ2D();        // �R���X�g���N�^
    void clear();   // �����o�ϐ��̃N���A
    void move();    // �ړ�
    void draw();    // �`��
    void draw_shadow();
    void Wall_check(int i);
	void obj_check(int i);
    void area_check();
};


class OBJ2DManager 
{
protected:
public:
    std::list<OBJ2D>  objList; 
public:
    // �f�X�g���N�^
    ~OBJ2DManager();

    void init();    // ������
    void update();  // �X�V
    void draw();    // �`��

    OBJ2D* add(MoveAlg* mvAlg, const VECTOR2& pos = VECTOR2(0, 0)); // objList�ɐV����OBJ2D��ǉ�����
    VECTOR2 get_position(OBJ2D a) { return a.position; }
    std::list<OBJ2D>* getList() { return &objList; }                // objList���擾����
};
#endif// ! INCLUDED_OBJ2D