#include "all.h"

using namespace GameLib;
VECTOR2     camera_pos_target = VECTOR2(0, 0);

OBJ2D*     camera_pos_target1 = nullptr;
OBJ2D*     camera_pos_target2 = nullptr;

float		camera_angle		= 45;
VECTOR2		camera_position		= VECTOR2(Ground::width * Ground::size_X / 2, Ground::width * Ground::size_Y / 2);
VECTOR2		zero_position		=  VECTOR2(camera_position.x + (system::SCREEN_WIDTH / zoom), camera_position.y + (system::SCREEN_WIDTH / zoom));
float		zoom = 1.0f;
float		zoom_target = 1;
float		angle_target = 0;
float		camera_scale_y = 0.6f;

int vibration_state = 0;
int zoom_state = 0;
int vibration_timer;
float vibration_width;
float vibration_hight;
VECTOR2 vibration_save;
float zoom_save;


void draw_pos_update(OBJ2D* it)
{
	if (zoom <= 0) { zoom = 1; }
	it->pos.x = it->position.x - camera_position.x;
	it->pos.y = it->position.y - camera_position.y;

	VECTOR2 temppos = it->pos;

	it->pos.x = temppos.x*cosf(ToRadian(camera_angle)) - temppos.y*sinf(ToRadian(camera_angle));
	it->pos.y = temppos.x*sinf(ToRadian(camera_angle)) + temppos.y*cosf(ToRadian(camera_angle));

	it->pos *= zoom;
	it->draw_scale = zoom*it->scale;

	it->pos.x += system::SCREEN_WIDTH/2;
    it->pos.y += system::SCREEN_HEIGHT / 2;

	it->pos.y *= camera_scale_y;

    //ˆÊ’uC³
	it->pos.y += 250;

	it->distance = it->pos.y - system::SCREEN_HEIGHT;

	if (it->isDraw3D)
	{
		for (int i = 0; i < 4; i++)
		{
			if (zoom <= 0)zoom = 1;
			it->is3Dpos[i].x = it->is3Dposition[i].x - camera_position.x;
			it->is3Dpos[i].y = it->is3Dposition[i].y - camera_position.y;

			VECTOR2 temppos= it->is3Dpos[i];

			it->is3Dpos[i].x = temppos.x*cosf(ToRadian(camera_angle)) - temppos.y*sinf(ToRadian(camera_angle));
			it->is3Dpos[i].y = temppos.x*sinf(ToRadian(camera_angle)) + temppos.y*cosf(ToRadian(camera_angle));

			it->is3Dpos[i] *= zoom;

			it->is3Dpos[i].x += system::SCREEN_WIDTH / 2;
			it->is3Dpos[i].y += system::SCREEN_HEIGHT / 2;

			it->is3Dpos[i].y *= camera_scale_y;

			it->is3Dpos[i].y += 250;		
		}
	}
}

VECTOR2 mouse_pos_get(float x, float y) 
{
    y -= 250;
    y /= camera_scale_y;

    y -= system::SCREEN_HEIGHT / 2;
    x -= system::SCREEN_WIDTH / 2;

    y /= zoom;
    x /= zoom;

    VECTOR2 temp = VECTOR2(x, y);

    x = temp.x*cosf(ToRadian(-camera_angle)) - temp.y*sinf(ToRadian(-camera_angle));
    y = temp.x*sinf(ToRadian(-camera_angle)) + temp.y*cosf(ToRadian(-camera_angle));

    y += camera_position.y;
    x += camera_position.x;

    return VECTOR2(x, y);    
}


void camera_update()
{
	using namespace input;

	camera_pos_target1 = &Game::instance()->playerManager()->objList.begin()._Ptr->_Myval;
	//camera_pos_target2 = &Game::instance()->enemyManager()->objList.begin()._Ptr->_Myval;

	if (input::TRG(0) & PAD_TRG2)		   ////ƒƒbƒNƒIƒ“
	{
		bool target_lock;
		VECTOR2 new_mouse_pso = mouse_pos_get(mousePos.x, mousePos.y+64);

		for (auto& it : Game::instance()->enemyManager()->objList)
		{
			target_lock = nullptr;
			if (Length(new_mouse_pso, it.position) < it.size*1.4)
			{
                if (Game::Tutorial_State == Game::TUTORIAL_LOCK && Game::instance()->substate == 1) 
				{
                    Game::instance()->substate = 2;
                }
				sound::play(10);
				camera_pos_target2 = &it;
				target_lock = true;
				break;
			}
			if (!target_lock)
			{
                if (Game::Tutorial_State == Game::TUTORIAL_LOCK && Game::instance()->substate == 2)
				{
                    Game::instance()->substate = 0;
                    Game::instance()->enemyManager()->objList.begin()->hp = 0;                  
                    Game::Tutorial_State = Game::TUTORIAL_ENEMY;
                }
				sound::play(11);
				camera_pos_target2 = nullptr;
			}
		}
	}

	if (camera_pos_target2 && camera_pos_target2->exist)
	{
		float x = camera_pos_target1->position.x - camera_pos_target2->position.x;
		float y = camera_pos_target1->position.y - camera_pos_target2->position.y;

		angle_target = ToDegree(ToRadian(90) - atan2(y, x));
		zoom_target = (system::SCREEN_HEIGHT / 2) / Length(camera_pos_target2->position, camera_pos_target1->position);
		camera_pos_target = (camera_pos_target1->position + camera_pos_target2->position) / 2;
	}
	else
	{
        camera_pos_target2 = nullptr;
		camera_pos_target = camera_pos_target1->position;
		zoom_target = 1;
		angle_target = camera_angle;
	}

	VECTOR2 camera_speed;
	camera_speed = (camera_pos_target- camera_position)*0.03;

	//camera_positionXV
	if (camera_pos_target.x - camera_position.x > -1 && camera_pos_target.x - camera_position.x < 1)
	{
		camera_speed.x = camera_pos_target.x - camera_position.x;
	}
	if (camera_pos_target.y - camera_position.y > -1 && camera_pos_target.y - camera_position.y < 1)
	{
		camera_speed.y = camera_pos_target.y - camera_position.y;
	}
	camera_position += camera_speed;

	//ZoomXV
	if (zoom_target > 1.2)zoom_target = 1.2;
	if (zoom_target < 0.7)zoom_target = 0.7;
	if (zoom != zoom_target)
	{
		if (zoom>zoom_target) { zoom *=0.999; }
		else { zoom *= 1.001; }
	}

	//angleXV
	if (angle_target >= 360)angle_target -= 360;
	if (angle_target < 0)angle_target += 360;
	if (camera_angle != angle_target)
	{
		if (angle_target - camera_angle<0.55&&angle_target - camera_angle>-0.55)
		{
			camera_angle = angle_target;
		}
		else if (angle_target > camera_angle)
		{
			if (angle_target - camera_angle < 180)
			{
				camera_angle += (angle_target - camera_angle)*0.02;
			}
			else
			{
				camera_angle -= (360 - angle_target + camera_angle)*0.02;
			}
		}
		else
		{
			if (camera_angle- angle_target < 180)
			{
				camera_angle -= (camera_angle - angle_target)*0.02;
			}
			else
			{
				camera_angle += (360 - camera_angle + angle_target)*0.02;
			}
		}
	}

	switch (vibration_state)
	{
	case 0:
		break;
	case 1://U“®
		vibration_save = {};
		vibration_state++;
		break;

	case 2:
		if (vibration_timer > 0)
		{
			camera_position.x += vibration_width;
			camera_position.y += vibration_hight;
			vibration_save.x += vibration_width;
			vibration_save.y += vibration_hight;

			if (vibration_timer % 2) 
			{
				vibration_width *= -1;
				vibration_width *= 0.94;
				vibration_hight *= -1;
				vibration_hight *= 0.94;
			}

			if (vibration_width < 0.1&&vibration_width >-0.1) { vibration_width = 0; }
			if (vibration_hight < 0.1&&vibration_hight >-0.1) { vibration_hight = 0; }
			vibration_timer--;
		}
		else { vibration_state++; }
		break;

	case 3:
		camera_position.x -= vibration_save.x;
		camera_position.y -= vibration_save.y;
		vibration_state = 0;
		break;
	}
	switch (zoom_state)
	{
	case 0:
		break;

	case 1:
		zoom_save = zoom;
		zoom_state++;
		break;

	case 2:
		zoom *= 1.02;
		if (zoom >= zoom_save*1.1)
		{
			zoom_state++;
		}
		break;

	case 3:
		zoom *= 0.98;
		if (zoom <= zoom_save)
		{
			zoom = zoom_save;
			zoom_state = 0;
		}
		break;
	}
	
	if (camera_angle >= 360) { camera_angle -= 360; }
	if (camera_angle < 0) { camera_angle += 360; }

}
void SetVibration(int timer, float width, float hight)
{
	if (vibration_state == 0)
	{
		vibration_timer = timer;
		vibration_width = width;//‰¡—h‚ê
		vibration_hight = hight;//c—h‚ê
		vibration_state++;
	}
}
