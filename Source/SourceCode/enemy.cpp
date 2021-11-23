#include "all.h"
using namespace GameLib;

void TutorialEnemy::move(OBJ2D *obj)
{
    using namespace input; 
    switch (obj->state)
    {
    case 0:
        obj->hp = 5;
        obj->data = sprEnemy1;
        obj->type = tENEMY2;
        obj->scale = VECTOR2(1, 1);
        obj->texPos = VECTOR2(0, 0);
        obj->texSize = VECTOR2(128, 128);
        obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y - 5);
        obj->color = VECTOR4(1, 1, 1, 1);
        obj->timer = 0;
        obj->size = 35;
        obj->height = 10;
        obj->state++;
        Game::instance()->gameuiManager()->ui_add(&hp, obj->position, 1, obj);
        break;

    case 1:
        if (obj->hp <= 0)
        {
            obj->timer = 0;
            obj->anime.y = 4;
            obj->state = 2;
        }

        switch (Game::Tutorial_State) 
		{
        case Game::TUTORIAL_ATTACK:
            for (int i = 0; i < 4; i++) 
			{
                if (obj->judgeFlag[i])
                {
                    switch (obj->judgeFlag[i]->type)
                    {
                    case tFIREBALL:
                        obj->hp--;
                        break;
                    }
                    obj->judgeFlag[i] = nullptr;
                }
            }
            break;     
        }

    case 2:
        break;

    case 3:
        obj->clear();
        Game::instance()->Tutorial_target->clear();
        Game::instance()->Tutorial_mark->clear();
        break;
    }
    
    animation_update(obj);
    obj->timer++;
}

void TutorialEnemy::animation_update(OBJ2D* obj) 
{
    VECTOR2 anmie_vec = VecRotation(NorVector(obj->speed), camera_angle);
    if (obj->hp <= 0)
    {
        obj->anime.x = obj->timer / 6 % 8;
		if (obj->anime.x >= 7) { obj->state = 3; }
    }
    else
    {
        if (anmie_vec.y <-0.5) { obj->anime.y = 1; }
        else if (anmie_vec.y >0.5) { obj->anime.y = 0; }
        else if (anmie_vec.x > 0) { obj->anime.y = 2; }
        else { obj->anime.y = 3; }
        obj->anime.x = obj->timer / 8 % 8;
    }
}

//--------------------------------
//  BOSS
//--------------------------------
void Enemy::move(OBJ2D *obj)
{
	using namespace input;

	switch (obj->state)
	{
	case 0:
		obj->hp = HP;
		obj->data		 = sprEnemy;
		obj->position	 = VECTOR2(700, 700);
		obj->type		 = tENEMY;
		obj->scale		 = VECTOR2(1, 1);
		obj->texPos		 = VECTOR2(0, 0);
		obj->texSize	 = VECTOR2(256, 256);
		obj->texPivot	 = VECTOR2(obj->texSize.x / 2, obj->texSize.y - 50);
		obj->color		 = VECTOR4(1, 1, 1, 1);
		obj->anime		 = VECTOR2(0, 0);
		obj->size		 = obj->texSize.x / 3;
        obj->height      = 10;
		obj->timer		 = 0;
		obj->speed		 = VECTOR2(0, 0);
		obj->state++;

		move_pt[0].pattern	 = 0;
		move_pt[1].pattern	 = 0;

		Game::instance()->groundManager()->add(&enemy_ground , Game::instance()->enemyManager()->objList.begin()->position);
		Game::instance()->groundManager()->add(&enemy_ground2, Game::instance()->enemyManager()->objList.begin()->position);
		Game::instance()->groundManager()->add(&enemy_ground3, Game::instance()->enemyManager()->objList.begin()->position);
		Game::instance()->groundManager()->add(&enemy_ground4, Game::instance()->enemyManager()->objList.begin()->position);
		Game::instance()->groundManager()->add(&enemy_ground5, Game::instance()->enemyManager()->objList.begin()->position);
        Game::instance()->gameuiManager()->ui_add(&hp, obj->position, 3, obj);
		break;

	case 1:
		obj->speed = {};
		if (obj->hp <= 0) { obj->clear(); }
		pattern_update(obj, &move_pt[0]);

		if (obj->hp <= 80) { pattern_update(obj, &move_pt[1]); }

		for (int i = 0; i < 4; i++) 
		{
			if (obj->judgeFlag[i])
			{
				switch (obj->judgeFlag[i]->type)
				{
				case tWall:
					obj->Wall_check(i);
					break;
                case tBOMB_FIREBALL:
				case tFIREBALL:
                    obj->hp -= 1.0f;
					break;
                case tBOMB:
                    obj->judgeFlag[i]->clear();
                    if (obj->hp <= 120)obj->hp += 0.2;
                    break;
				}
			}
            obj->judgeFlag[i] = nullptr;
		}
		animation_update(obj);
		obj->position += obj->speed;
		break;			
	}
	obj->timer++;
}
void Enemy::pattern_update(OBJ2D* obj, Move_Pattern* m)
{
	switch (m->pattern)
	{
	case 0:
		m->timer = 0;
		m->state = 0;
		m->pl_pos = {};
		if (obj->hp < 30) { m->pattern = rand() % 6 + 1; }
		else if (obj->hp < 70) { m->pattern = rand() % 4 + 1; }
		else { m->pattern = rand() % 3 + 1; }

		if (move_pt[0].pattern == move_pt[1].pattern) { m->pattern++; }
		if (m->pattern > 6) { m->pattern = 1; }
		break;
	case 1:
		pattern01(obj, m);
		break;
	case 2:
		pattern02(obj, m);
		break;
	case 3:
		pattern03(obj, m);
		break;
	case 4:
		pattern04(obj, m);
		break;
	case 5:
		pattern05(obj, m);
		break;
	case 6:
		pattern06(obj, m);
		break;
	}
	m->timer++;
}
void Enemy::animation_update(OBJ2D* obj) 
{
	VECTOR2 anmie_vec = VecRotation(NorVector(obj->speed), camera_angle);

	if (anmie_vec.y <-0.5) { obj->anime.y = 1; }
	else if (anmie_vec.y >0.5) { obj->anime.y = 0; }
	else if (anmie_vec.x > 0) { obj->anime.y = 2; }
	else { obj->anime.y = 3; }

	obj->anime.x = obj->timer / 8 % 8;
}
void Enemy::pattern01(OBJ2D* obj, Move_Pattern* m) //’Ç‚¢‚©‚¯
{
	switch (m->state)
	{
	case 0:
		for (auto& it : Game::instance()->playerManager()->objList)
		{
			obj->speed = NorVector(it.position, obj->position) * 3;
		}
		if (m->timer > 180) { m->state++; }
		break;
	case 1:
		m->pattern = 0;
		break;
	}
}

void Enemy::pattern02(OBJ2D* obj, Move_Pattern* m) //’Êí’e
{
	switch (m->state)
	{
	case 0:
		if (m->timer % 30 == 0)
		{
			Game::instance()->effectManager()->add(&bossfireball, VECTOR2(obj->position.x, obj->position.y), 1, NorVector(Game::instance()->playerManager()->objList.begin()->position, obj->position));
		}
		if (m->timer > 150) { m->state++; }
		break;
	case 1:
		m->pattern = 0;
		break;
	}
}
void Enemy::pattern03(OBJ2D* obj, Move_Pattern* m) //uŠÔˆÚ“®
{
	switch (m->state)
	{
	case 0:
		if (m->timer == 120)
		{
			m->pl_pos = Game::instance()->playerManager()->objList.begin()->position;
			Game::instance()->groundManager()->add(&bossteleport, VECTOR2(m->pl_pos.x, m->pl_pos.y));
			m->state++;
		}
		break;
	case 1:
		if (m->timer > 180) { m->state++; }
		break;
	case 2:
		obj->position = m->pl_pos;
		sound::play(8);
		m->state++;
		break;
	case 3:
		m->pattern = 0;
		break;
	}
}
void Enemy::pattern04(OBJ2D* obj, Move_Pattern* m) //’ÇŒ‚’e
{
	switch (m->state)
	{
	case 0:
		if (m->timer % 60 == 0)
		{
			Game::instance()->effectManager()->add(&bosspursuitball, VECTOR2(obj->position.x, obj->position.y), 1, NorVector(Game::instance()->playerManager()->objList.begin()->position, obj->position));
		}
		if (m->timer > 300) { m->state++; }
		break;
	case 1:
		m->pattern = 0;
		break;
	}
}
void Enemy::pattern05(OBJ2D* obj, Move_Pattern* m) //‚Æ‚Ä[‚à‚Â‚¨[‚¢
{
	switch (m->state)
	{
	case 0:
		if (m->timer % 120 == 0)
		{
			for (int i = 0; i <= 360; i += 10)
			{
				Game::instance()->effectManager()->add(&bossnomalball,
					VECTOR2(obj->position.x, obj->position.y), 1,
					NorVector(VECTOR2(cosf(i), sinf(i)), VECTOR2(0, 0)));
			}
			sound::play(12);
		}
		if (m->timer > 600) { m->state++; }
		break;
	case 1:
		m->pattern = 0;
		break;
	}
}
void Enemy::pattern06(OBJ2D* obj, Move_Pattern* m) //‰J
{
	OBJ2D* pl = &(Game::instance()->playerManager()->objList.begin()._Ptr->_Myval);
	switch (m->state)
	{
	case 0:
		if (obj->timer % 30 == 0)
		{
			Game::instance()->effectManager()->add(&bossrain, VECTOR2(pl->position.x + pl->speed.x * 190, pl->position.y +  pl->speed.y * 190), 1, VECTOR2(0, 0));
		}
		if (m->timer >= 300) { m->state++; }
		break;
	case 1:
		m->pattern = 0;
		break;
	}
}

void Enemy_Ground::move(OBJ2D* obj) 
{
	switch (obj->state)
	{
	case 0:
		obj->data = sprBoss_Skill_Ground;
		obj->anime = VECTOR2(0, 0);
		obj->scale = VECTOR2(1, camera_scale_y);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(300, 300);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->size = obj->texSize.x / 4;
		obj->timer = 0;
		obj->state++;
	case 1:
		obj->angle += 0.008;
		obj->position = Game::instance()->enemyManager()->objList.begin()->position;
		if (boss.move_pt[0].pattern == 6 || boss.move_pt[1].pattern == 6) { obj->anime.y = 1; }
		else { obj->anime.y = 0; }
		if (Game::instance()->enemyManager()->objList.empty()) 
		{
			obj->state++;
		}
		break;
	case 2:
		obj->clear();
		break;
	}
}
void Enemy_Ground2::move(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		obj->data = sprBoss_Skill_Ground;
		obj->anime = VECTOR2(1, 0);
		obj->scale = VECTOR2(1, camera_scale_y);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(300, 300);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->size = obj->texSize.x / 4;
		obj->timer = 0;
		obj->state++;
	case 1:
		obj->angle += 0.008;
		obj->position = Game::instance()->enemyManager()->objList.begin()->position;
		if (boss.move_pt[0].pattern == 2 || boss.move_pt[1].pattern == 2)obj->anime.y = 1;
		else obj->anime.y = 0;
		if (Game::instance()->enemyManager()->objList.empty()) 
		{
			obj->state++;
		}
		break;
	case 2:
		obj->clear();
		break;
	}
}
void Enemy_Ground3::move(OBJ2D* obj) 
{
	switch (obj->state)
	{
	case 0:
		obj->data = sprBoss_Skill_Ground;
		obj->anime = VECTOR2(2, 0);
		obj->scale = VECTOR2(1, camera_scale_y);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(300, 300);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->size = obj->texSize.x / 4;
		obj->timer = 0;
		obj->state++;

	case 1:
		obj->angle += 0.008;
		obj->position = Game::instance()->enemyManager()->objList.begin()->position;
		if (boss.move_pt[0].pattern == 4 || boss.move_pt[1].pattern == 4) { obj->anime.y = 1; }
		else { obj->anime.y = 0; }
		if (Game::instance()->enemyManager()->objList.empty())
		{
			obj->state++;
		}
		break;
	case 2:
		obj->clear();
		break;
	}
}
void Enemy_Ground4::move(OBJ2D* obj) 
{
	switch (obj->state)
	{
	case 0:
		obj->data = sprBoss_Skill_Ground;
		obj->anime = VECTOR2(3, 0);
		obj->scale = VECTOR2(1, camera_scale_y);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(300, 300);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->size = obj->texSize.x / 4;
		obj->timer = 0;
		obj->state++;

	case 1:
		obj->angle += 0.008;
		obj->position = Game::instance()->enemyManager()->objList.begin()->position;
		if (boss.move_pt[0].pattern == 5 || boss.move_pt[1].pattern == 5) { obj->anime.y = 1; }
		else { obj->anime.y = 0; }
		if (Game::instance()->enemyManager()->objList.empty()) 
		{
			obj->state++;
		}
		break;
	case 2:
		obj->clear();
		break;
	}
}
void Enemy_Ground5::move(OBJ2D* obj) 
{
	switch (obj->state)
	{
	case 0:
		obj->data = sprBoss_Skill_Ground;
		obj->anime = VECTOR2(4, 0);
		obj->scale = VECTOR2(1, camera_scale_y);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(300, 300);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->size = obj->texSize.x / 4;
		obj->timer = 0;
		obj->state++;

	case 1:
		obj->angle += 0.008;
		obj->position = Game::instance()->enemyManager()->objList.begin()->position;
		if (boss.move_pt[0].pattern == 3 || boss.move_pt[1].pattern == 3) { obj->anime.y = 1; }
		else { obj->anime.y = 0; }
		if (Game::instance()->enemyManager()->objList.empty())
		{
			obj->state++;
		}
		break;
	case 2:
		obj->clear();
		break;
	}
}
//--------------------------------
//  ŽG‹›
//--------------------------------
void Enemy2::move(OBJ2D *obj)
{
	using namespace input;  
	switch (obj->state)
	{
	case 0:
		obj->hp = 5;
		obj->data = sprEnemy1;
		obj->type = tENEMY2;
		obj->scale = VECTOR2(1, 1);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(128, 128);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y - 5);
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->timer = 0;
		obj->size = 35;
		obj->height = 10;
		obj->state++;
		Game::instance()->gameuiManager()->ui_add(&hp, obj->position, 1, obj);
		break;

	case 1:
		if (obj->hp <= 0)
		{
			obj->timer = 0;
			obj->anime.y = 4;
			obj->state = 2;
		}

		pattern_update(obj, &move_pt[0]);
		//pattern_update(obj, &move_pt[1]);

		for (int i = 0; i < 4; i++) 
		{
			if (obj->judgeFlag[i])
			{
				switch (obj->judgeFlag[i]->type)
				{
				case tWall:
					obj->Wall_check(i);
					break;
				case tENEMY2:
					obj->obj_check(i);
					break;
                case tBOMB_FIREBALL:
				case tFIREBALL:
					obj->hp--;
					break;
				}
				obj->judgeFlag[i] = nullptr;
			}
		}
		obj->position += obj->speed;
		obj->position += obj->nock_back;

		obj->nock_back *= 0.8f;
		if (obj->nock_back.x<1 && obj->nock_back.x>-1) { obj->nock_back.x = 0; }
		if (obj->nock_back.y<1 && obj->nock_back.y>-1) { obj->nock_back.y = 0; }
		obj->area_check();
		break;

	case 2:
		obj->type = tNOTHING;
		break;

	case 3:
		obj->clear();
		count--;
		break;
	}
	animation_update(obj);
	if (obj->timer / 30 % 2) { obj->height += 0.5; }
	else { obj->height -= 0.5; }
	obj->timer++;
}
void Enemy2::pattern_update(OBJ2D* obj, Move_Pattern* m)
{
	pattern01(obj, m);
	switch (m->pattern)
	{
	case 0:
		m->timer = 0;
		m->state = 0;
		m->pl_pos = {};
		m->pattern = 2;		
		break;
	case 1:
		break;
	case 2:
		pattern02(obj, m);
		break;
	case 5:
		break;
	}
	m->timer++;
}
void Enemy2::animation_update(OBJ2D* obj)
{
	VECTOR2 anmie_vec = VecRotation(NorVector(obj->speed), camera_angle);
	if (obj->hp <= 0)
	{
		obj->anime.x = obj->timer / 6 % 8;
		if (obj->anime.x >= 7)obj->state = 3;
	}
	else
	{
		if (anmie_vec.y <-0.5) { obj->anime.y = 1; }
		else if (anmie_vec.y >0.5) { obj->anime.y = 0; }
		else if (anmie_vec.x > 0) { obj->anime.y = 2; }
		else { obj->anime.y = 3; }
		obj->anime.x = obj->timer / 8 % 8;
	}
}
void Enemy2::pattern01(OBJ2D* obj, Move_Pattern* m) //’Ç‚¢‚©‚¯
{
	switch (m->state)
	{
	case 0:
		for (auto& it : Game::instance()->playerManager()->objList)
		{
			obj->speed = NorVector(it.position, obj->position) * 1.5;
			obj->position += obj->speed;
		}
		if (m->timer > 180) m->state++;
		break;
	case 1:
		m->pattern = 0;
		break;
	}
}
void Enemy2::pattern02(OBJ2D* obj, Move_Pattern* m) //’Êí’e
{
	switch (m->state)
	{
	case 0:
		if (m->timer % 60 == 0)
		{
			Game::instance()->effectManager()->add(&zakonomalball, VECTOR2(obj->position.x, obj->position.y), 1, NorVector(Game::instance()->playerManager()->objList.begin()->position, obj->position));
		}
		if (m->timer > 600) { m->state++; }
		break;
	case 1:
		m->pattern = 0;
		break;
	}
}




