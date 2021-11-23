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
    OBJ2D obj;                          // OBJ2Dを宣言する
    obj.mvAlg = mvAlg;                  // mvAlgに引数のmvalgを代入
    obj.position = pos;                 // positionに引数のposを代入
    obj.scale = VECTOR2(1, 1);          // スケールは等倍
    obj.color = VECTOR4(1, 1, 1, 1);    // 色は白（不透明度1.0f）
    objList.push_back(obj);             // リストにobjを追加する
    return &(*objList.rbegin());        // 今追加したobjのアドレスを返す（何かで使えるように）
};

void GroundManager::draw()
{
    for (auto& it : objList)            // objListの全ての要素をループし、itという名前で各要素にアクセス 
    {
		it.draw();                      // itのdrawメソッドを呼ぶ
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

