#include "all.h"
using namespace GameLib;

void OBJ_UI::init()
{

}

void OBJ_UI::draw()
{
	sprite_render(
		data,														// 使用するスプライト
		pos.x, pos.y,											// 位置
		scale.x, scale.y,											// スケール
		texPos.x + (texSize.x*anime), texPos.y,					// 元画像位置
		texSize.x, texSize.y,										// 元画像大きさ
		texPivot.x, texPivot.y,										// 基準点の位置
		angle,
		color.x, color.y, color.z, color.w
		);
}


OBJ_UI* UIManager::add(UI_Alg* uiAlg, const VECTOR2& pos)
{
	OBJ_UI		obj;                  
	obj.click = 0;
	obj.state = 0;
	obj.uiAlg = uiAlg;                
	obj.pos   = pos;                  
    obj.angle = 0;
	obj.scale = VECTOR2(1, 1);        
	obj.color = VECTOR4(1, 1, 1, 1);  

	UI_List.push_back(obj);           
	return &(*UI_List.rbegin());      
}

void GameUIManager::update() 
{
    for (auto& it : objList)          
    {
        it.move();                    
        if (!it.screen_drow) 
		{
            draw_pos_update(&it);
        }
    }
    objList.remove_if([](OBJ2D i) {return !(i.exist); });
}

void GameUIManager::draw() 
{
    for (auto& it : objList)           
    {
        if (it.mvAlg == &ui_full) 
		{
            GameLib::setBlendMode(Blender::BS_ADD);
        }

        if (it.data == sprPlayer_skill)
		{
            primitive::circle(VECTOR2(it.pos.x + 1.5, it.pos.y -1), it.size + 1.5, VECTOR4(0.9, 0.9, 0.9, 0.2), 64);
        }
        it.draw();
        GameLib::setBlendMode(Blender::BS_ALPHA);
    }
}

OBJ2D* GameUIManager::ui_add(MoveAlg* mvAlg, const VECTOR2& pos, int type,OBJ2D*p) 
{
    OBJ2D obj;                          
    obj.mvAlg = mvAlg;                  
    obj.position = pos;                 
    obj.scale = VECTOR2(1, 1);          
    obj.color = VECTOR4(1, 1, 1, 1);    
    obj.move_pattern = type;
    obj.P = p;
    objList.push_back(obj);             
    return &(*objList.rbegin());        
}



void HP::move(OBJ2D*obj)
{
    using namespace input; 

    switch (obj->move_pattern) 
	{
    case 1://内枠(雑魚敵)
        switch (obj->state)
        {
        case 0:           
            obj->data = sprEnemy_hp;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 10);
            obj->texSize = VECTOR2(91, 20);
            obj->texPivot = VECTOR2(obj->texSize.x / 2, 130);
            obj->color = VECTOR4(1, 0, 1, 1);
            obj->screen_drow = false;
            Game::instance()->gameuiManager()->ui_add(&hp, obj->position, 2,obj->P);
            obj->state++;
            break;

        case 1:
            obj->position = VECTOR2(obj->P->position.x, obj->P->position.y);

            obj->texSize.x = (obj->P->hp / 5.0f) * 91;

            if (obj->P->hp <= 0 || obj->P ==nullptr)
			{
                obj->clear();
            }
            break;
        }
        break;

    case 2://外枠(雑魚敵)
        switch (obj->state)
        {
        case 0:
            obj->data = sprEnemy_hp;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(91, 10);
            obj->texPivot = VECTOR2(obj->texSize.x / 2, 130);
            obj->color = VECTOR4(1, 0, 1, 1);
            obj->screen_drow = false;
            obj->state++;
            break;

        case 1:
            obj->position = VECTOR2(obj->P->position.x, obj->P->position.y);
            if (obj->P->hp <= 0)
			{
                obj->clear();
            }
            break;
        }
        break;

    case 3://内枠(ボス)
        switch (obj->state)
        {
        case 0:
            obj->data = sprBoss_hp;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 28);
            obj->texSize = VECTOR2(174, 28);
			obj->texPivot = VECTOR2(obj->texSize.x / 2 - 26 , 230);
            obj->color = VECTOR4(1, 0, 1, 1);
            obj->screen_drow = false;
            Game::instance()->gameuiManager()->ui_add(&hp, obj->position, 4, obj->P);
            obj->state++;
            break;

        case 1:
            obj->position = VECTOR2(obj->P->position.x, obj->P->position.y);
            obj->texSize.x = (obj->P->hp / boss.HP) * 143;
            if (obj->P->hp <= 0) 
			{
                obj->clear();
            }
            break;
        }
        break;

    case 4://外枠(ボス)
        switch (obj->state)
        {
        case 0:      
            obj->data = sprBoss_hp;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(174, 28);
            obj->texPivot = VECTOR2(obj->texSize.x / 2, 230);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->screen_drow = false;
            obj->state++;
            break;

        case 1:
            obj->position = VECTOR2(obj->P->position.x, obj->P->position.y);
            if (obj->P->hp <= 0) 
			{
                obj->clear();
            }
            break;
        }
        break;

    case 5://内枠(自機)
        switch (obj->state)
        {
        case 0:
            obj->data = sprPlayer_wave_hp;
            obj->pos = VECTOR2(55, 800);
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(256, 256);
            obj->texPivot = VECTOR2(0, 0);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->draw_scale = VECTOR2(1, 1);
            obj->screen_drow = true;
            obj->anime = VECTOR2(0,0);
            Game::instance()->gameuiManager()->ui_add(&hp, obj->position, 6, obj->P);
            obj->state++;
            break;

        case 1:
            obj->position = VECTOR2(obj->P->position.x, obj->P->position.y);
            obj->anime.x = obj->timer / 8 % 8;            
            obj->anime.y = (int)(10 - obj->P->hp);
            obj->timer++;
            if (obj->P->hp <= 0) 
			{
                obj->clear();
            }
            break;
        }
        break;

    case 6://外枠(自機)
        switch (obj->state)
        {
        case 0:        
            obj->data = sprPlayer_hp;
            obj->pos = VECTOR2(50, 800);
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(267, 253);
            obj->texPivot = VECTOR2(0, 0);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->draw_scale = VECTOR2(1,1);
            obj->screen_drow = true;
            obj->state++;
            break;
        case 1:
            break;
        }
        break;
    }
}

void Skill::move(OBJ2D*obj)
{
    switch (obj->move_pattern) 
	{
    case 1://スキル1
        switch (obj->state)
        {
        case 0:
            obj->data = sprPlayer_skill1;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(64, 64);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->draw_scale = VECTOR2(1, 1);
            obj->pos = VECTOR2(460, 965);
            obj->screen_drow = true;
            Game::instance()->gameuiManager()->ui_add(&skill, obj->position, 2, obj->P);
            obj->state++;
            break;

        case 1:
            if (Player::skill1_timer == 1) 
			{
                Game::instance()->gameuiManager()->ui_add(&ui_full, obj->position, 2, obj);
            }
            break;
        }
        break;

    case 2://スキル1(枠)
        switch (obj->state)
        {
        case 0:
            obj->data = sprPlayer_skill;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(64, 64);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->pos = VECTOR2(460, 960);
            obj->draw_scale = VECTOR2(1, 1);
            obj->screen_drow = true;
            obj->state++;
            break;

        case 1:
            obj->size = 41 - (Player::skill1_timer * 41 / 50);       
            break;
        }
        break;

    case 3://スキル2
        switch (obj->state)
        {
        case 0:
            obj->data = sprPlayer_skill2;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(64, 64);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->draw_scale = VECTOR2(1, 1);
            obj->pos = VECTOR2(590, 965);
            obj->screen_drow = true;
            Game::instance()->gameuiManager()->ui_add(&skill, obj->position, 4, obj->P);
            obj->state++;
            break;
        case 1:
            if (Player::skill2_timer == 1)
			{
                Game::instance()->gameuiManager()->ui_add(&ui_full, obj->position, 0, obj);
            }
            break;
        }
        break;

    case 4://スキル2(枠)
        switch (obj->state)
        {
        case 0:
            obj->data = sprPlayer_skill;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(128*2, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(64, 64);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->pos = VECTOR2(590, 960);
            obj->draw_scale = VECTOR2(1, 1);
            obj->screen_drow = true;
            obj->state++;
            break;

        case 1:
            obj->size = 41 - (Player::skill2_timer * 41 / 50);        
            break;
        }
        break;

    case 5://スキル3
        switch (obj->state)
        {
        case 0:
            obj->data = sprBomb;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(64, 64);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->draw_scale = VECTOR2(1, 1);
            obj->pos = VECTOR2(720, 965);
            obj->screen_drow = true;
            obj->anime = VECTOR2(3, 1);
            Game::instance()->gameuiManager()->ui_add(&skill, obj->position, 6, obj->P);
            obj->state++;
            break;
        case 1:
            if (Player::skill3_timer == 1) 
			{
                Game::instance()->gameuiManager()->ui_add(&ui_full, obj->position, 0, obj);
            }
            break;
        }
        break;

    case 6://スキル3(枠)
        switch (obj->state)
        {
        case 0:
            obj->data = sprPlayer_skill;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(128, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(64, 64);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->pos = VECTOR2(720, 960);
            obj->draw_scale = VECTOR2(1, 1);
            obj->screen_drow = true;
            obj->state++;
            break;

        case 1:
            obj->size = 41 - (Player::skill3_timer * 41 / 50);           
            break;
        }
        break;

    case 7://スキル4
        switch (obj->state)
        {
        case 0:
            obj->data = sprPlayer_skill3;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(0, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(64, 64);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->draw_scale = VECTOR2(1, 1);
            obj->pos = VECTOR2(855, 960);
            obj->screen_drow = true;
            Game::instance()->gameuiManager()->ui_add(&skill, obj->position, 8, obj->P);

            obj->state++;

            break;
        case 1:
            
            break;
        }
        break;

    case 8://スキル4(枠)
        switch (obj->state)
        {
        case 0:
            obj->data = sprPlayer_skill;
            obj->scale = VECTOR2(1, 1.0f);
            obj->texPos = VECTOR2(128*3, 0);
            obj->texSize = VECTOR2(128, 128);
            obj->texPivot = VECTOR2(64, 64);
            obj->color = VECTOR4(1, 1, 1, 1);
            obj->pos = VECTOR2(850, 960);
            obj->draw_scale = VECTOR2(1, 1);
            obj->screen_drow = true;
            obj->state++;
            break;

        case 1:
            obj->size = 41;
            break;
        }
        break;
    }
}

void UI_FULL::move(OBJ2D*obj) 
{
    switch (obj->state)
    {
    case 0:
		if (obj->P->data == sprPlayer_skill1) { obj->texPos = VECTOR2(0, 0); }
		if (obj->P->data == sprPlayer_skill2) { obj->texPos = VECTOR2(128 * 2, 0); }
		if (obj->P->data == sprBomb) { obj->texPos = VECTOR2(128, 0); }
        obj->data = sprPlayer_skill;
        obj->scale = VECTOR2(1, 1.0f);
        obj->texSize = VECTOR2(128, 128);
        obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
        obj->color = VECTOR4(1, 1, 1, 0.1);
        obj->pos = VECTOR2(obj->P->pos.x - 0.33, obj->P->pos.y - 4.8);
        obj->draw_scale = VECTOR2(1, 1);
        obj->screen_drow = true;
        obj->state++;
        state = 0;
        break;

    case 1:
        switch (state) 
		{
        case 0:
            obj->color.w *= 1.1;
			if (obj->color.w >= 0.3) { state++; }
            break;
        case 1:
            obj->color.w *= 0.9;
			if (obj->color.w <= 0.01) { obj->clear(); }
            break;
        }
    }
}

void CLEAR::move(OBJ2D*obj) 
{
    switch (obj->state)
    {
    case 0:
        obj->data = sprClear;
        obj->scale = VECTOR2(1, 1.0f);
        obj->texPos = VECTOR2(0, 0);
        obj->texSize = VECTOR2(1920, 1080);
        obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
        obj->color = VECTOR4(1, 1, 1, 0.1);
        obj->pos = VECTOR2(0, 0);
        obj->draw_scale = VECTOR2(1, 1);
        obj->screen_drow = true;
        obj->state++;
        break;

    case 1:
        break;
    }
}

void UIManager::init()
{
	UI_List.clear();
}

bool istouch(OBJ_UI *it) 
{
	if (it->circle)
	{
		return(Length(mousePos, it->pos) <= it->size.x);
	}
	else
	{
		float x = mousePos.x - it->pos.x;
		float y = mousePos.y - it->pos.y;
		if (x < 0) { x *= -1; }
		if (y < 0) { y *= -1; }
		if (x < (it->size.x / 2) && y < (it->size.y / 2)) { return true; }
	}
	return false;
}

void UIManager::update()
{
	using namespace input;

	for (auto& it : UI_List)           
	{
		if (it.state == 0)
		{
			it.uiAlg->init(&it);
			it.state++;
		}
		if (istouch(&it)) 
		{
			it.anime = 1;
			if (TRG(0) & PAD_START) { it.click = 1; }
			if (it.click == 1)
			{
				if (STATE(0) & PAD_START)
				{
					it.uiAlg->touch_updata(&it);
					it.anime = 2;
				}
				if (TRG_RELEASE(0) & PAD_START)
				{
					it.uiAlg->click_updata(&it);
				}
			}
		}
		else { it.anime = 0; it.click = 0; }
	}
}

void UIManager::draw()
{
	for (auto& it : UI_List)           
	{
		it.draw();
	}
}

UIManager::~UIManager()
{
	UI_List.clear();
}
