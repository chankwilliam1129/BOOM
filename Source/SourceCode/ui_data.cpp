#include "all.h"
using namespace GameLib;

void UI_START::init(OBJ_UI* obj)
{
	obj->state = 0;
	obj->data = spruiStart;
	obj->circle = true;
	obj->scale = VECTOR2(1, 1);
	obj->texPos = VECTOR2(0, 0);
	obj->texSize = VECTOR2(768, 704);
	obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
	obj->color = VECTOR4(1, 1, 1, 1);
	obj->size = VECTOR2(348, 0);
}

void UI_START::click_updata(OBJ_UI* obj)
{
	Title::instance()->changeScene(Game::instance());
	Game::instance()->setTutorialState(Game::TUTORIAL_MOVE);
}

void UI_BOSS_START::init(OBJ_UI* obj)
{
    obj->state = 0;
    obj->data = sprBoss_skip;
    obj->circle = true;
    obj->scale = VECTOR2(1, 1);
    obj->texPos = VECTOR2(0, 0);
    obj->texSize = VECTOR2(384, 384);
    obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
    obj->color = VECTOR4(1, 1, 1, 1);
    obj->size = VECTOR2(160, 0);
}

void UI_BOSS_START::click_updata(OBJ_UI* obj)
{
    Title::instance()->changeScene(Game::instance());
	Game::instance()->setTutorialState(Game::MAINGAME);
}

void UI_TITLE::init(OBJ_UI* obj)
{
	obj->state = 0;
	obj->data = spruiTitle;
	obj->circle = true;
	obj->scale = VECTOR2(1, 1);
	obj->texPos = VECTOR2(0, 0);
	obj->texSize = VECTOR2(300, 300);
	obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
	obj->color = VECTOR4(1, 1, 1, 1);
	obj->size = VECTOR2(150, 0);
}
void UI_TITLE::click_updata(OBJ_UI* obj)
{
	Game::instance()->changeScene(Title::instance());
}

void UI_GAME::init(OBJ_UI* obj)
{
	obj->state = 0;
	obj->data = spruiGame;
	obj->circle = true;
	obj->scale = VECTOR2(1, 1);
	obj->texPos = VECTOR2(0, 0);
	obj->texSize = VECTOR2(300, 300);
	obj->texPivot = VECTOR2(obj->texSize.x / 2, obj->texSize.y / 2);
	obj->color = VECTOR4(1, 1, 1, 1);
	obj->size = VECTOR2(150, 0);
}
void UI_GAME::click_updata(OBJ_UI* obj)
{
	Game::instance()->isPaused = (!Game::instance()->isPaused);
}


void TUTO_MOVE::move(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		obj->data = sprtutorial_move;
		obj->angle = 0;
		obj->scale = VECTOR2(1, camera_scale_y);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(128, 121);
		obj->texPivot = obj->texSize / 2;
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->size = obj->texSize.y / 2;
		obj->state++;
		break;

	case 1:
		obj->angle += ToRadian(0.2);
		break;
	}
}

void TUTO_TARGET::move(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		obj->data = sprtutorial_target;
		obj->angle = 0;
		obj->height = 160;
		obj->scale = VECTOR2(1, 1);
		obj->texPos = VECTOR2(0, 0);
		obj->texSize = VECTOR2(47, 40);
		obj->texPivot = obj->texSize / 2;
		obj->color = VECTOR4(1, 1, 1, 1);
		obj->size = obj->texSize.y / 2;
		obj->speed.x = 0.1;
		obj->speed.y = 0;
		obj->state++;
		break;

	case 1:
		obj->timer++;
		obj->height += obj->speed.x;
		if (obj->timer > 100)
		{
			obj->speed.x *= -1;
			obj->timer = 0;
		}
		break;
	}
}