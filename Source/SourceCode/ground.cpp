#include"all.h"
using namespace GameLib;

float shortestDistance;

int ground_check[Ground::height][Ground::width] =
{
    1,1,1,1,1,1,1,1,1,1,
	1,0,1,1,1,1,1,1,0,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,0,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,0,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,0,1,1,1,1,1,1,0,1,
	1,1,1,1,1,1,1,1,1,1,
};

void Ground::move(OBJ2D* obj) 
{
    switch (obj->state)
    {
    case 0:  
        obj->data = sprGround;
		obj->type = tGROUND;
        obj->angle = ToRadian(camera_angle);
		obj->scale = VECTOR2(1, camera_scale_y);
        obj->texPos = VECTOR2(0, 0);
        obj->texSize = VECTOR2(256, 256);
        obj->texPivot = VECTOR2(128, 128);
        obj->color = VECTOR4(1, 1, 1, 1);
        obj->size = obj->texSize.x/2;        
        obj->state++;
        break;

    case 1:
        obj->angle = ToRadian(camera_angle);
        break;
    }   
}

OBJ2D* GroundManager::add2(MoveAlg* mvAlg, int ground_check, const VECTOR2& pos)
{
    OBJ2D obj;                          // OBJ2D��錾����
    obj.mvAlg = mvAlg;                  // mvAlg�Ɉ�����mvalg����
    obj.position = pos;                 // position�Ɉ�����pos����
    obj.scale = VECTOR2(1, 1);          // �X�P�[���͓��{
    obj.color = VECTOR4(1, 1, 1, 1);    // �F�͔��i�s�����x1.0f�j
    objList.push_back(obj);             // ���X�g��obj��ǉ�����
    return &(*objList.rbegin());        // ���ǉ�����obj�̃A�h���X��Ԃ��i�����Ŏg����悤�Ɂj
};

void GroundManager::draw()
{
    for (auto& it : objList)            // objList�̑S�Ă̗v�f�����[�v���Ait�Ƃ������O�Ŋe�v�f�ɃA�N�Z�X 
    {
		it.draw();                      // it��draw���\�b�h���Ă�
        GameLib::setBlendMode(Blender::BS_ALPHA);
    }
}

void Pillar::move(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		obj->data = sprGround2;
		obj->type = tWall;
		obj->angle = ToRadian(camera_angle);
		obj->scale = VECTOR2(1, camera_scale_y);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(256, 256);
		obj->texPivot = VECTOR2(128, 128);
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->size = obj->texSize.x / 2;
		obj->isDraw3D = true;
		obj->is3DSize = 200;

		obj->is3Dposition[0] = VECTOR2(obj->position.x - obj->size, obj->position.y - obj->size);
		obj->is3Dposition[1] = VECTOR2(obj->position.x + obj->size, obj->position.y - obj->size);
		obj->is3Dposition[2] = VECTOR2(obj->position.x + obj->size, obj->position.y + obj->size);
		obj->is3Dposition[3] = VECTOR2(obj->position.x - obj->size, obj->position.y + obj->size);
		obj->state++;
		break;

	case 1:
		obj->angle = ToRadian(camera_angle);
    
		break;
	}
}

