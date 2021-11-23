#include"all.h"
using namespace GameLib;

//PLAYER
void Fire::use(OBJ2D* obj,int move_pattern,VECTOR2 vec) 
{
    Game::instance()->effectManager()->add(&fireball, VECTOR2(obj->position.x, obj->position.y), move_pattern,vec);
	sound::play(0);
}
void FireBall::move(OBJ2D*obj)
{
	switch (obj->move_pattern) 
	{
	case 1:
		switch (obj->state)
		{
		case 0:
			obj->data = sprFireball;
			obj->type = tFIREBALL;
			obj->scale = VECTOR2(1, 1);
			obj->texPos = VECTOR2(0, 0);
			obj->texSize = VECTOR2(128, 128);
			obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
			obj->height = 64;
			obj->color = VECTOR4(1, 1, 1, 1);
			obj->velocity = 22;
			obj->speed *= obj->velocity;
			obj->size = 10;
			obj->timer = 0;
			obj->state++;
            break;
		case 1:
			if (obj->timer > 60) { obj->state++; }
			for (int i = 0; i < 4; i++) 
			{
				if (obj->judgeFlag[i]) 
				{
					switch (obj->judgeFlag[i]->type)
					{
					case tWall:
						if (obj->position.x - obj->size >= obj->judgeFlag[i]->is3Dposition[0].x && obj->position.x + obj->size <= obj->judgeFlag[i]->is3Dposition[1].x)
						{
							obj->speed.y *= -1;
						}
						else if (obj->position.y - obj->size >= obj->judgeFlag[i]->is3Dposition[0].y && obj->position.y + obj->size <= obj->judgeFlag[i]->is3Dposition[3].y)
						{
							obj->speed.x *= -1;
						}
						else { obj->speed = NorVector(obj->position, obj->judgeFlag[i]->position)*obj->velocity; }
						break;

					case tENEMY:
					case tENEMY2:
						obj->state = 2;
                        obj->type = tNOTHING;
						SetVibration(4, 2, 2);
						sound::play(1);
						break;

					case tENEMY_SKILL:
                    case tBOMB:                                 
					case tENEMY_SKILL3:
						obj->state = 2;
						break;
                      
					default:
						break;
					}
				}
				obj->judgeFlag[i] = nullptr;
			}
			
			Game::instance()->effectManager()->add(&fireball, VECTOR2(obj->position.x, obj->position.y), 2, VECTOR2(0, 0));

			break;
		case 2:
			Game::instance()->effectManager()->add(&fireball, VECTOR2(obj->position.x, obj->position.y), 3, VECTOR2(0, 0));
			obj->clear();
			break;
		}
		break;

	case 2:
		switch (obj->state)
		{
		case 0:
			obj->data = sprFireball;
			obj->scale = VECTOR2(1, 1);
			obj->texPos = VECTOR2(0, 0);
			obj->texSize = VECTOR2(128, 128);
			obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
			obj->height = 64;
			obj->color = VECTOR4(1, 1, 1, 1);
			obj->size = obj->texSize.x / 2;
			obj->timer = 0;
			obj->state++;
            break;
		case 1:
			if (obj->scale.x < 0.1) { obj->state++; }
			obj->scale *= 0.9;
			obj->color.w *= 0.92;
			break;
		case 2:
			obj->clear();
			break;
		}
		break;

	case 3:
		switch (obj->state)
		{
		case 0:
			obj->data = sprFireball;
			obj->scale = VECTOR2(1, 1);
			obj->texPos = VECTOR2(0, 0);
			obj->texSize = VECTOR2(128, 128);
			obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
			obj->height = 64;
			obj->color = VECTOR4(1, 1, 1, 1);
			obj->size = obj->texSize.x / 2;
			obj->timer = 0;
			obj->state++;
            break;
		case 1:
			if (obj->timer > 5)obj->state++;
			obj->scale *= 1.4;
			obj->color.w *= 0.92;

			break;
		case 2:
			obj->clear();
			break;
		}
		break;
	}
	obj->position += obj->speed;
	obj->timer++;
}
void BombFireBall::move(OBJ2D*obj) 
{
    switch (obj->move_pattern) 
	{
    case 1:
        switch (obj->state)
        {
        case 0:
            obj->data = sprFireball;
            obj->type = tBOMB_FIREBALL;
            obj->scale = VECTOR2(1, 1);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
            obj->height = 64;
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->velocity = 22;
            obj->speed *= obj->velocity;
            obj->size = 10;
            obj->timer = 0;
            obj->state++;
            break;
        case 1:
			if (obj->timer > 60) { obj->state++; }
            for (int i = 0; i < 4; i++) 
			{
                if (obj->judgeFlag[i])
                {
                    switch (obj->judgeFlag[i]->type)
                    {
                    case tWall:
                        obj->speed = NorVector(obj->position, obj->judgeFlag[i]->position)*obj->velocity;
                        break;

                    case tENEMY:
                        obj->state = 2;
                        obj->type = tNOTHING;
                        SetVibration(4, 2, 2);
                        break;

                    case tENEMY2:
                        obj->state = 2;
                        obj->type = tNOTHING;
                        SetVibration(4, 2, 2);
                        break;

                    case tENEMY_SKILL:
                        obj->state = 2;
                        break;

                    case tBOMB:
                        obj->state = 2;
                        break;

                    case tENEMY_SKILL3:
                        obj->state = 2;
                        break;

                    default:
                        break;
                    }
                }
                obj->judgeFlag[i] = nullptr;
            }

            Game::instance()->effectManager()->add(&fireball, VECTOR2(obj->position.x, obj->position.y), 2, VECTOR2(0, 0));

            break;
        case 2:
            Game::instance()->effectManager()->add(&fireball, VECTOR2(obj->position.x, obj->position.y), 3, VECTOR2(0, 0));
            obj->clear();
            break;
        }
        break;

    case 2:
        switch (obj->state)
        {
        case 0:        
            obj->data = sprFireball;
            obj->scale = VECTOR2(1, 1);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
            obj->height = 64;
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->size = obj->texSize.x / 2;
            obj->timer = 0;
            obj->state++;
            break;
        case 1:
            if (obj->scale.x < 0.1)obj->state++;
            obj->scale *= 0.9;
            obj->color.w *= 0.92;
            break;
        case 2:
            obj->clear();
            break;
        }
        break;

    case 3:
        switch (obj->state)
        {
        case 0:
            obj->data = sprFireball;
            obj->scale = VECTOR2(1, 1);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
            obj->height = 64;
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->size = obj->texSize.x / 2;
            obj->timer = 0;
            obj->state++;
            break;
        case 1:
            if (obj->timer > 5)obj->state++;
            obj->scale *= 1.4;
            obj->color.w *= 0.92;

            break;
        case 2:
            obj->clear();
            break;
        }
        break;
    }
    obj->position += obj->speed;
    obj->timer++;
}
void Avoid::use(OBJ2D* obj, int move_pattern, VECTOR2 vec)
{
    for (int i = 0; i < 20; i++)
    {     
        Game::instance()->effectManager()->add(&avoid_move, VECTOR2(obj->position.x, obj->position.y), move_pattern, vec);
		sound::play(2);
    }

    p = &Game::instance()->playerManager()->objList.begin()._Ptr->_Myval;
    p->position += NorVector(obj->speed, VECTOR2(0, 0)) * 300;
}
void Avoid_Move::move(OBJ2D*obj)
{
    using namespace input;
    switch (obj->state)
    {
    case 0:
        obj->data = sprAvoid;
        obj->scale = VECTOR2(2, 2);
        obj->texPos = VECTOR2(0, 0);
        obj->texSize = VECTOR2(128, 128);
        obj->texPivot = obj->texSize / 2;
        obj->color = VECTOR4(1, 1, 1, 1);
        obj->height = 0;        
        obj->size = obj->texSize.x / 2;
        obj->anime.y = rand() % 4;
        obj->color = VECTOR4(1,1,1,1);
        obj->timer = 0;       
        obj->state++;        
        break;
    case 1:
        obj->position -= obj->speed*obj->timer;
        if (obj->timer < 5) 
		{
            obj->scale *= 0.7;
        }
        else 
		{
            obj->scale *= 1.3;
        }
        obj->timer++;
		if (obj->timer > 10) { obj->state++; }
        break;
    case 2:
        obj->clear();
    }
}

void BOMB_SET::use(OBJ2D* obj, int move_pattern, VECTOR2 vec)
{
    Game::instance()->effectManager()->add(&bomb, mouse_pos_get(mousePos.x, mousePos.y + 64), 1, VECTOR2(0, 0));
	sound::play(5);
}
void BOMB::move(OBJ2D*obj)
{
    using namespace input;
        switch (obj->state)
        {
        case 0:
            obj->data = sprBomb;
            obj->scale = VECTOR2(1, 1);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
            obj->height = 64;
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->velocity = 10;
            obj->size = obj->texSize.x / 6;
            obj->timer = 0;
            obj->type = tBOMB;
            obj->state++;
            break;
        case 1:
            for (int i = 0; i < 4; i++)
			{
                if (obj->judgeFlag[i])
                {
                    switch (obj->judgeFlag[i]->type)
                    {
                    case tBOMB_FIREBALL:
                    case tFIREBALL:
                        if (Game::Tutorial_State == Game::TUTORIAL_BOOM && Game::instance()->substate == 2)
						{
                            Game::instance()->substate = 0;
                            Game::Tutorial_State = Game::TUTORIAL_LOCK;
                        }
						sound::play(4);
                        Game::instance()->effectManager()->add(&bombfireball, VECTOR2(obj->position.x, obj->position.y), 1, NorVector(obj->judgeFlag[i]->speed));
                        Game::instance()->effectManager()->add(&bombfireball, VECTOR2(obj->position.x, obj->position.y), 1, VecRotation(NorVector(obj->judgeFlag[i]->speed),30.0f));
                        Game::instance()->effectManager()->add(&bombfireball, VECTOR2(obj->position.x, obj->position.y), 1, VecRotation(NorVector(obj->judgeFlag[i]->speed), -30.0f));                   
                        obj->judgeFlag[i]->clear();
                        obj->clear();
                        break;
                    case tENEMY_SKILL3:
                        obj->clear();
                        break;
                    }
                    obj->judgeFlag[i] = nullptr;
                }
            }

            obj->anime.x = obj->timer / 3 % 4;
			if (obj->anime.x == 3) { obj->anime.y = 1; }
			if (obj->timer / 40 % 2) { obj->height += 0.2f; }
			else { obj->height -= 0.2f; }
            obj->timer++;
            break;
        }
}

//BOSS
void BossNomalBall::move(OBJ2D*obj)
{
	using namespace input;
	switch (obj->state)
	{
	case 0:
		obj->data = sprBoss_Shot;
		obj->type = tENEMY_SKILL;
		obj->scale = VECTOR2(1, 1);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(128, 128);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
		obj->height = 64;
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->velocity = 5;
		obj->speed *= obj->velocity;
		obj->size = 13;
		obj->timer = 0;
		obj->anime = VECTOR2(0, 0);
		obj->state++;
	case 1:
		obj->position += obj->speed;
        obj->anime.x = obj->timer / 8 % 8;
		if (obj->timer >= 300)obj->state++;
		for (int i = 0; i < 4; i++) 
		{
			if (obj->judgeFlag[i])
			{
				switch (obj->judgeFlag[i]->type)
				{
				case tWall:
					obj->state = 2;
					break;

				case tPLAYER:
					obj->state = 2;
					SetVibration(4, 2, 2);
					break;

                case tBOMB_FIREBALL:
				case tFIREBALL:
					obj->state = 2;
					break;
				default:
					break;
				}
			}
			obj->judgeFlag[i] = nullptr;
		}
		break;

	case 2:
		obj->clear();
		break;
	}
	obj->timer++;
}

void BossFireBall::move(OBJ2D*obj) 
{
	VECTOR2 new_speed;
	VECTOR2 plpos;

	using namespace input;

	switch (obj->state)
	{
	case 0:
		obj->data = sprBoss_Shot;
		obj->type = tENEMY_SKILL3;
		obj->scale = VECTOR2(1, camera_scale_y);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(128, 128);
		obj->texPivot = VECTOR2(64, 64);
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->velocity = 15;
		obj->speed *= obj->velocity;
		obj->size = 35;
		obj->height = 64;
		obj->timer = 0;
		obj->anime = VECTOR2(0, 1);
		sound::play(9);
		obj->state++;

	case 1:
		new_speed = NorVector(obj->speed, VECTOR2(0, 0));
		plpos = Game::instance()->playerManager()->objList.begin()->position;
		obj->speed = NorVector(obj->speed, VECTOR2(0, 0));
		obj->angle -= 0.5;
		if ((obj->timer + 15) / 30 % 2) 
		{
			new_speed.x = obj->speed.x*cosf(ToRadian(5)) - obj->speed.y*sinf(ToRadian(5));
			new_speed.y = obj->speed.x*sinf(ToRadian(5)) + obj->speed.y*cosf(ToRadian(5));
		}
		else
		{
			new_speed.x = obj->speed.x*cosf(ToRadian(-5)) - obj->speed.y*sinf(ToRadian(-5));
			new_speed.y = obj->speed.x*sinf(ToRadian(-5)) + obj->speed.y*cosf(ToRadian(-5));

		}
		obj->speed = new_speed*obj->velocity;
		obj->position += obj->speed;
        obj->anime.x = obj->timer / 8 % 8;
		for (int i = 0; i < 4; i++)
		{
			if (obj->judgeFlag[i])
			{
				switch (obj->judgeFlag[i]->type)
				{
				case tWall:
                case tBOMB:
					obj->state = 2;
					break;

				case tPLAYER:
					obj->state = 2;
					SetVibration(4, 2, 2);
					break;            
             
				default:
					break;
				}
			}
			obj->judgeFlag[i] = nullptr;
		}
		if (obj->timer > 120) { obj->state = 2; }
		break;

	case 2:
		obj->clear();
		break;
	}
	obj->timer++;
}

void BossTeleport::move(OBJ2D*obj) 
{
	using namespace input;
	switch (obj->state)
	{
	case 0:
		obj->data = sprBoss_Ground;
		obj->type = tENEMY_GROUND;
		obj->scale = VECTOR2(1, camera_scale_y);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(128, 128);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
		obj->height = 1;
		obj->color = VECTOR4(1, 1, 1, 0.3);
		obj->velocity = 5;
		obj->speed *= obj->velocity;
		obj->size = 5;
		obj->timer = 0;
		obj->state++;
	case 1:
		obj->color.w *= 1.03;
		if (obj->color.w >= 1.0f) { obj->color.w = 1.03; }
		if (obj->timer > 60) { obj->state++; }
		break;
	case 2:
		obj->clear();
		break;
	}
	obj->timer++;
}

void BossPursuitBall::move(OBJ2D*obj) 
{
	VECTOR2 plpos;
	VECTOR2 new_speed;
	using namespace input;

	switch (obj->state)
	{
	case 0:
		obj->data = sprBoss_Shot;
		obj->type = tENEMY_SKILL;
		obj->scale = VECTOR2(1, 1);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(128, 128);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
		obj->height = 64;
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->velocity = 10;
		obj->speed *= obj->velocity;
		obj->size = 22;
		obj->timer = 0;
		obj->anime = VECTOR2(0, 2);
		sound::play(13);
		obj->state++;
	case 1:
		plpos = Game::instance()->playerManager()->objList.begin()->position;
		if (obj->timer % 4 == 0)
		{
			if (cross(obj->position, obj->position + obj->speed, plpos) > 0)
			{
				new_speed.x = obj->speed.x*cosf(ToRadian(4)) - obj->speed.y*sinf(ToRadian(4));
				new_speed.y = obj->speed.x*sinf(ToRadian(4)) + obj->speed.y*cosf(ToRadian(4));
			}
			else
			{
				new_speed.x = obj->speed.x*cosf(ToRadian(-4)) - obj->speed.y*sinf(ToRadian(-4));
				new_speed.y = obj->speed.x*sinf(ToRadian(-4)) + obj->speed.y*cosf(ToRadian(-4));

			}
			obj->speed = new_speed;
		}
        obj->anime.x = obj->timer / 8 % 8;
		obj->position += obj->speed;
		if (obj->timer >= 300)obj->state++;
		for (int i = 0; i < 4; i++) 
		{
			if (obj->judgeFlag[i])
			{
				switch (obj->judgeFlag[i]->type)
				{
				case tWall:
                    obj->speed = NorVector(obj->position, obj->judgeFlag[i]->position)*obj->velocity;
					break;

				case tPLAYER:
					obj->state = 2;
					SetVibration(4, 2, 2);
					break;

                case tBOMB_FIREBALL:
				case tFIREBALL:
					obj->state = 2;
					break;
				default:
					break;
				}
			}
			obj->judgeFlag[i] = nullptr;
		}
		break;
	case 2:
		obj->clear();
		break;
	}
	obj->timer++;
}

void BossRain::move(OBJ2D*obj)
{
	using namespace input;
	switch (obj->move_pattern)
	{
	case 1:
		switch (obj->state)
		{
		case 0:
			obj->data = sprBoss_Shot;
			obj->type = tSHADOW;
			obj->scale = VECTOR2(1, 1);
			obj->texPos = VECTOR2(0, 384);
			obj->texSize = VECTOR2(128, 256);
			obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y - 60);
			obj->height = 1000;
			obj->color = VECTOR4(1, 1, 1, 1);
			obj->size = 20;
			obj->timer = 0;
			obj->anime = VECTOR2(0, 0);
			sound::play(7);
			obj->state++;
			break;
		case 1:
			obj->height -= 30;
			if (obj->timer % 8 == 0)
			{
				obj->anime.x = obj->timer % 5;
			}

			if (obj->timer > 35)
			{
				VECTOR2 plpos = Game::instance()->playerManager()->objList.begin()->position;
				Game::instance()->effectManager()->add(&bossrain, obj->position, 2, VECTOR2(0, 0));
				obj->clear();
			}
			obj->area_check();
			break;
		}
		break;	

	case 2:
		switch (obj->state)
		{
		case 0:
			obj->data = sprBoss_Shot;
			obj->type = tENEMY_SKILL4;
			obj->scale = VECTOR2(1, 1);
			obj->texPos = VECTOR2(0, 384);
			obj->texSize = VECTOR2(128, 256);
			obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y - 67);
			obj->height = 0;
			obj->color = VECTOR4(1, 1, 1, 1);
			obj->size = 23;
			obj->timer = 0;
			obj->anime = VECTOR2(7, 0);
			sound::play(6);
			obj->state++;
			break;
		case 1:
			for (int i = 0; i < 4; i++) 
			{
				if (obj->judgeFlag[i])
				{
					switch (obj->judgeFlag[i]->type)
					{
					case tPLAYER:
						SetVibration(7, 10, 10);
						break;
					default:
						break;
					}
				}
				obj->judgeFlag[i] = nullptr;
			}
            obj->anime.x = obj->timer / 8 % 8;

			if (obj->anime.x > 7) { obj->anime.x = 7; }

			obj->scale *= 1.07;
			obj->size *= 1.07;
			obj->color.w *= 0.95;
			if (obj->timer >= 10) { obj->state = 3; }
			break;

		case 3:
			obj->clear();
			break;
		}
		break;
	}
	obj->timer++;
}

//ŽG‹›
void ZakoNomalBall::move(OBJ2D*obj)
{
	using namespace input;
	switch (obj->state)
	{
	case 0:
		obj->data = sprBoss_Shot;
		obj->type = tENEMY_SKILL2;
		obj->scale = VECTOR2(1, 1);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(128, 128);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
		obj->anime = VECTOR2(0, 5);
		obj->height = 64;
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->velocity = 5;
		obj->speed *= obj->velocity;
		obj->size = 15;
		obj->timer = 0;
		obj->state++;
	case 1:
		obj->position += obj->speed;
		obj->angle--;
		if (obj->timer >= 300)obj->state++;
		for (int i = 0; i < 4; i++) 
		{
			if (obj->judgeFlag[i])
			{
				switch (obj->judgeFlag[i]->type)
				{
				case tWall:
					obj->state = 2;
					break;

				case tPLAYER:
					obj->state = 2;
					SetVibration(4, 2, 2);
					break;

				case tFIREBALL:
					obj->state = 2;
					break;
				default:
					break;
				}
			}
			obj->judgeFlag[i] = nullptr;
		}
		break;
	case 2:
		obj->clear();
		break;
	}
	obj->timer++;
}
