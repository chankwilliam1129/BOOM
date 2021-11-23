#include "all.h"
using namespace GameLib;

extern float camera_angle;

int Player::skill1_timer = 0;
int Player::skill2_timer = 0;
int Player::skill3_timer = 0;
bool BOMB_SET::areaflg = false;

void PlayerManager::update()
{
    for (auto& it : objList)           
    {
        it.move();                    
    }
    objList.remove_if([](OBJ2D i) {return !(i.exist); });
}

void Player::move(OBJ2D *obj)
{
    using namespace input;

    switch (obj->state)
    {
    case 0:
		obj->hp = 10;
		obj->data		= sprPlayer;
		obj->position   = VECTOR2(1300, 1300);
		obj->type		= tPLAYER;
		obj->scale		= VECTOR2(1, 1.0f);
		obj->texPos		= VECTOR2(0, 0);
		obj->texSize	= VECTOR2(128, 128);
		obj->texPivot   = VECTOR2(obj->texSize.x / 2, obj->texSize.y - 10);
		obj->color		= VECTOR4(1, 1, 1, 1);
		obj->anime      = VECTOR2(0, 0);
        obj->size		= 20;
		obj->timer		= 0;
        obj->speed      = VECTOR2(0, 0);
        obj->state++;

        skill1 = new Fire;		//ファイアスキル 
        skill2 = new Avoid;		//回避スキル
        skill3 = new BOMB_SET;	//ボム設置
        lock_target = nullptr;

        Game::instance()->gameuiManager()->ui_add(&hp, obj->position, 5, obj);		//HP
        Game::instance()->gameuiManager()->ui_add(&skill, obj->position, 1, obj);	//スキル1
        Game::instance()->gameuiManager()->ui_add(&skill, obj->position, 3, obj);	//スキル2
        Game::instance()->gameuiManager()->ui_add(&skill, obj->position, 5, obj);	//スキル3
        Game::instance()->gameuiManager()->ui_add(&skill, obj->position, 7, obj);	//スキル4
        break;

    case 1:
        move_update(obj);

        if (obj->hp <= 0.0f)
        {
            obj->clear();
        }

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
				case tENEMY:					
				case tENEMY_SKILL:
                case tENEMY_SKILL2:
				case tENEMY_SKILL3:
                    
					if (!obj->invincible_timer)
					{
                        obj->nock_back = NorVector(obj->position, obj->judgeFlag[i]->position) * 40;
                        if (Game::Tutorial_State == Game::TUTORIAL_STATE::MAINGAME) 
						{
                            obj->hp -= 1.0f;
                        }
						obj->invincible_timer = 120;                     
                        SetVibration(7, 10, 10);
						sound::play(3);
					}
					break;
				case tENEMY_SKILL4:
					
					if (!obj->invincible_timer)
					{
                        obj->nock_back = NorVector(obj->position, obj->judgeFlag[i]->position) * 80;
						obj->hp -= 1.5f;
						obj->invincible_timer = 120;
                        SetVibration(7, 10, 10);
						sound::play(3);
					}
					break;
				}
				obj->judgeFlag[i] = nullptr;
			}
		}
		       
        pos_update(obj);
        draw_pos_update(obj);
        skill_update(obj);
		animation_update(obj);
        obj->area_check();
        break; 
    }
    obj->timer++;
}


void Player_Ground::move(OBJ2D* obj) 
{
	using namespace input;
	switch (obj->state)
	{
	case 0:
		obj->data = sprPlayer_Ground;
		obj->position = Game::instance()->playerManager()->objList.begin()->position;
		obj->scale = VECTOR2(1, camera_scale_y);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(128, 128);
		obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->size = obj->texSize.x / 4;
		obj->timer = 0;
		obj->state++;

	case 1:
		obj->position = Game::instance()->playerManager()->objList.begin()->position;
		obj->angle = ToRadian(camera_angle);

		float x = obj->position.x - mouse_pos_get(mousePos.x, mousePos.y).x;
		float y = obj->position.y - mouse_pos_get(mousePos.x, mousePos.y).y;
		float pg_angle = atan2(y, x);
		obj->angle += pg_angle - ToRadian(90);
		break;
	}
}

BOOL SkillAlg::areaCheck(OBJ2D* obj, float limit)
{
    if (obj->pos.x < -limit ||
        obj->pos.x > system::SCREEN_WIDTH + limit ||
        obj->pos.y < -limit ||
        obj->pos.y > system::SCREEN_HEIGHT + limit)
    {
        obj->exist = FALSE;
    }

    return obj->exist;
}

void Player::move_update(OBJ2D* obj)
{
    using namespace input;
    obj->speed = {};

    if (STATE(0) & PAD_UP)
	{
        obj->speed.x -= cosf(ToRadian(90.0f - camera_angle));
        obj->speed.y -= sinf(ToRadian(90.0f - camera_angle));
    }

    if (STATE(0) & PAD_DOWN)
	{
        obj->speed.x += cosf(ToRadian(90.0f - camera_angle));
        obj->speed.y += sinf(ToRadian(90.0f - camera_angle));
    }

    if (STATE(0) & PAD_LEFT) 
	{
        obj->speed.x -= cosf(ToRadian(camera_angle));
        obj->speed.y += sinf(ToRadian(camera_angle));
    }

    if (STATE(0) & PAD_RIGHT)
	{
        obj->speed.x += cosf(ToRadian(camera_angle));
        obj->speed.y -= sinf(ToRadian(camera_angle));	
    }

    if (obj->speed != VECTOR2(0, 0))
    {
        obj->speed = NorVector(obj->speed, VECTOR2(0, 0));
    }
	if (skill1_timer >= skill1->Casting_TIME) { obj->speed /= 2.0f; }
}

void Player::pos_update(OBJ2D* obj)
{  
    obj->position += (obj->speed*PlayerManager::PLAYER_MOVE);
    obj->position += obj->nock_back;

    obj->nock_back *= 0.8f;
	if (obj->nock_back.x<1 && obj->nock_back.x>-1) { obj->nock_back.x = 0; }
	if (obj->nock_back.y<1 && obj->nock_back.y>-1) { obj->nock_back.y = 0; }
}

void Player::skill_update(OBJ2D* obj) 
{
    using namespace input;
    //ファイアスキル
    if ((TRG(0) & PAD_START) && Player::skill1_timer == 0)
    {
        temp = mouse_pos_get(mousePos.x, mousePos.y + 64);
        Player::skill1_timer = skill1->CoolDown_TIME;
        obj->timer = 0;
    }

    if (Player::skill1_timer == skill1->Casting_TIME)
    {
		skill1->use(obj, 1, NorVector(temp, obj->position));
    }
    if (Player::skill1_timer == skill1->Casting_TIME - 15)
    {
        skill1->use(obj, 1, NorVector(temp, obj->position));
    }
	if (Player::skill1_timer == skill1->Casting_TIME - 30)
    {
        skill1->use(obj, 1, NorVector(temp, obj->position));
    }

    //回避スキル
    if (obj->speed != VECTOR2(0, 0)) 
	{
        if ((TRG(0) & PAD_L1) && Player::skill2_timer == 0) 
		{
            Player::skill2_timer = skill2->CoolDown_TIME;
            lock_target = nullptr;
            obj->color.w = 0;
        }
    }
    if (Player::skill2_timer == skill2->Casting_TIME)
    {      
        skill2->use(obj, 1, obj->speed);
        obj->color.w = 1.0;        
    }

    //ボム設置   
    if (areaCheck(mouse_pos_get(mousePos.x, mousePos.y + 64), 0, 0, Ground::width * Ground::size_X, Ground::height * Ground::size_Y)) { BOMB_SET::areaflg = false; }
    else { BOMB_SET::areaflg = true; }

    for (auto& it : Game::instance()->effectManager()->objList)
	{
        if (it.mvAlg == &pillar) 
		{
            if (areaCheck(mouse_pos_get(mousePos.x, mousePos.y + 64), it.position.x - it.size * 1.2, it.position.y - it.size * 1.2, it.position.x + it.size * 1.2, it.position.y + it.size * 1.2))
			{
                BOMB_SET::areaflg = true;
            }
        }
    }

    for (auto& it : Game::instance()->effectManager()->objList) 
	{
        if (it.type == tBOMB)
		{
            if (circleHitCheck(mouse_pos_get(mousePos.x, mousePos.y + 64), it.size, it.position, it.size))
			{
                BOMB_SET::areaflg = true;
            }
        }
    }

    if (BOMB_SET::areaflg == false) 
	{
        if ((STATE(0) & PAD_TRG4) && Player::skill3_timer == 0) { Player::skill3_timer = skill3->CoolDown_TIME; }
    }

    if (Player::skill3_timer == skill3->Casting_TIME) { skill3->use(obj, 1, obj->speed); }

    BOMB_SET::areaflg = false;

	if (Player::skill1_timer > 0) { Player::skill1_timer--; }
	if (Player::skill2_timer > 0) { Player::skill2_timer--; }
	if (Player::skill3_timer > 0) { Player::skill3_timer--; }
}

void Player::animation_update(OBJ2D* obj)
{
    VECTOR2 anmie_vec = NorVector(mousePos, obj->pos);

    if (anmie_vec.y <-0.5) { obj->anime.y = 1; }
    else if (anmie_vec.y >0.5) { obj->anime.y = 0; }
    else if (anmie_vec.x > 0) { obj->anime.y = 2; obj->scale.x = 1; }
    else { obj->anime.y = 2; obj->scale.x = -1; }

    obj->anime.x = obj->timer / 8 % 8;
    if (Player::skill1_timer >= skill1->Casting_TIME)
    {
        obj->anime.y += 3;
        obj->anime.x = obj->timer / 2 % 8;
    }
    	
    if (obj->invincible_timer) 
	{
        obj->color.w = obj->invincible_timer / 3 % 2;
        obj->invincible_timer--;
    }
    else if (Player::skill2_timer < skill2->Casting_TIME) 
	{
        obj->color.w = 1;
    }
}