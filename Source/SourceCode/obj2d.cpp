#include "all.h"

using namespace GameLib;

OBJ2D::OBJ2D()
{
    clear();
	anime = VECTOR2(0, 0);
    scale = VECTOR2(1, 1);          
    color = VECTOR4(1, 1, 1, 1);   
	exist = true;
	state = 0;
	timer = 0;
}


void OBJ2D::clear()
{
	exist = false;
	hp = 0;
	type = tNOTHING;

	data = nullptr;
	anime = {};
	position = {};
	is3Dposition[4] = {};

	pos = {};
	scale = {};
	draw_scale = {};
	texPos = {};
	texSize = {};
	texPivot = {};
	height = 0;
	angle = 0;
	color = {};
	distance = 0;

	isDraw3D = false;
	is3DSize = {};
	is3Dpos[4] = {};


	mvAlg = nullptr;
	move_pattern = 0;
	state = 0;
	timer = 0;

	invincible_timer = 0;
	size = {};
	velocity = 0;
	speed = {};

	judgeFlag[0] = nullptr;
	judgeFlag[1] = nullptr;
	judgeFlag[2] = nullptr;
	judgeFlag[3] = nullptr;
	nock_back = {};

    P = nullptr;
    screen_drow = false;
}


void OBJ2D::move()
{
	if (mvAlg) { mvAlg->move(this); }
}

void OBJ2D::draw()
{
	if (isDraw3D) 
	{
		if (camera_angle > 90 && camera_angle < 270) 
		{
			primitive::quad({ is3Dpos[0],is3Dpos[1],
				is3Dpos[1] - VECTOR2(0,is3DSize*zoom),
				is3Dpos[0] - VECTOR2(0,is3DSize*zoom) },
				VECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
		}
		if (camera_angle < 180)
		{
			primitive::quad({ is3Dpos[1],is3Dpos[2],
				is3Dpos[2] - VECTOR2(0,is3DSize*zoom),
				is3Dpos[1] - VECTOR2(0,is3DSize*zoom) },
				VECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
		}
		if (camera_angle < 90 || camera_angle > 270)
		{
			primitive::quad({ is3Dpos[2],is3Dpos[3],
				is3Dpos[3] - VECTOR2(0,is3DSize*zoom),
				is3Dpos[2] - VECTOR2(0,is3DSize*zoom) },
				VECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
		}
		if (camera_angle> 180)
		{
			primitive::quad({ is3Dpos[3],is3Dpos[0],
				is3Dpos[0] - VECTOR2(0,is3DSize*zoom),
				is3Dpos[3] - VECTOR2(0,is3DSize*zoom) },
				VECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
		}

		pos = (is3Dpos[1] - VECTOR2(0, is3DSize*zoom)) + (is3Dpos[3] - VECTOR2(0, is3DSize*zoom));
		pos /= 2;
		sprite_render2(data,										
			pos.x, pos.y,												
			draw_scale.x, draw_scale.y,									
			texPos.x + anime.x*texSize.x, texPos.y + anime.y*texSize.y,										
			texSize.x, texSize.y,										
			texPivot.x, texPivot.y,										
			angle,
			color.x, color.y, color.z, color.w
			);

	}
	else if (data)                                      
	{      
		sprite_render2(data,											
			pos.x, pos.y - (height*zoom),										
			draw_scale.x, draw_scale.y,									
			texPos.x + anime.x*texSize.x, texPos.y + anime.y*texSize.y,								
			texSize.x, texSize.y,									
			texPivot.x, texPivot.y,										
			angle,
			color.x, color.y, color.z, color.w
			);
	}
}

void OBJ2D::draw_shadow()
{
    if (!(type == tWall || type == tNOTHING))
    {
        sprite_render2(sprShadow,
            pos.x, pos.y,
            size*0.02*zoom, size*0.02*camera_scale_y*zoom,
            0, 0,
            100, 100,
            50, 50,
            0,
            1, 1, 1, 1
            );
    }
}

void OBJ2DManager::init()
{
    objList.clear();
}


OBJ2D* OBJ2DManager::add(MoveAlg* mvAlg, const VECTOR2& pos)
{
    OBJ2D obj;                         
    obj.mvAlg = mvAlg;                 
    obj.position = pos;                
    obj.scale = VECTOR2(1, 1);         
    obj.color = VECTOR4(1, 1, 1, 1);   

    objList.push_back(obj);            
    return &(*objList.rbegin());       
}


void OBJ2DManager::update()
{
    for (auto& it : objList)
	{
		it.move();
        draw_pos_update(&it);  
    }
    objList.remove_if([](OBJ2D i) {return !(i.exist); });
}

bool obj2dsort(const OBJ2D a, const OBJ2D b) { return a.distance < b.distance; }

void OBJ2DManager::draw()
{
	for (auto& it : objList) { it.draw(); }
}

OBJ2DManager::~OBJ2DManager()
{
    objList.clear();
}

void OBJ2D::Wall_check(int i) 
{
	if (position.y < judgeFlag[i]->is3Dposition[0].y) { position.y = judgeFlag[i]->is3Dposition[0].y - size - 1; }
	else if (position.y > judgeFlag[i]->is3Dposition[2].y) { position.y = judgeFlag[i]->is3Dposition[2].y + size + 1; }
	else if (position.x < judgeFlag[i]->is3Dposition[0].x) { position.x = judgeFlag[i]->is3Dposition[0].x - size - 1; }
	else if (position.x > judgeFlag[i]->is3Dposition[2].x) { position.x = judgeFlag[i]->is3Dposition[2].x + size + 1; }
    else
    {
        while (SquareHitCheck(judgeFlag[i]->is3Dposition, position, size))
        {
			if (speed.x || speed.y) { position -= speed; }
			else if (nock_back.x || nock_back.y) { position -= nock_back; }
			else { position.y--; }
        }
    }
}

void OBJ2D::obj_check(int i) 
{
	nock_back = NorVector(position, judgeFlag[i]->position) * 1;
}

void OBJ2D::area_check() 
{
	if (position.x < 0 + size) { position.x = size; }
	if (position.x > 2560 - size) { position.x = 2560 - size; }
	if (position.y < 0 + size) { position.y = size; }
	if (position.y > 2560 - size) { position.y = 2560 - size; }
}