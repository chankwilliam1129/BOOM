#include "all.h"

using namespace GameLib;

Game Game::instance_;
int Game::Tutorial_State = 0;
int Game::Tutorial_Count = 0;
int num = 0;

void all_judge_updata(std::list<OBJ2D*> list);

void Game::init()
{
	Scene::init();	    
    bgManager_ = new BGManager;
	playerManager_ = new PlayerManager;
	enemyManager_ = new EnemyManager;
	groundManager_ = new GroundManager;
	effectManager_ = new EffectManager;
	uiManager_ = new UIManager;
    gameuiManager_ = new GameUIManager;
	isPaused = false;  
    substate = 0;
	pauseState = 0;
    Tutorial_Count = 0;
	sound_load();
	
	camera_pos_target1 = nullptr;
	camera_pos_target2 = nullptr;
	camera_angle = 45;
}


void Game::update()
{
	using namespace input;
	
    if (Tutorial_State != GAME_WIN && Tutorial_State != GAME_LOSE)
    {
        if (TRG(0) & PAD_SELECT) { isPaused = !isPaused; }
    }
 
	if (isPaused)
	{
		switch (pauseState)
		{
		case 0:
			uiManager()->add(&ui_title, VECTOR2(system::SCREEN_WIDTH / 2 - 200, system::SCREEN_HEIGHT / 2));
			uiManager()->add(&ui_game, VECTOR2(system::SCREEN_WIDTH / 2 + 200, system::SCREEN_HEIGHT / 2));
			pauseState++;
			break;
		case 1:
			uiManager()->update();
			break;
		}
		return;
	}
	else
	{
		pauseState = 0;
		uiManager()->UI_List.clear();
	}

	switch (state)
	{
	case 0:
		timer = 0;
		GameLib::setBlendMode(Blender::BS_ALPHA);   
		Tutorial_target = nullptr;
        bgManager()->init();
		playerManager()->init();
        playerManager()->add(&player, VECTOR2(1700, 1700));
        enemyManager()->init();		
		groundManager()->init();
		effectManager()->init();

		for (int y = 0; y < Ground::height; y++) 
		{
			for (int x = 0; x < Ground::width; x++)
			{
				switch (ground_check[x][y]) 
				{
				case 0:
					effectManager()->add(&pillar, VECTOR2(x * Ground::size_X + 128, y * Ground::size_Y + 128),0,VECTOR2(0,0));
					break;
				case 1:
					groundManager()->add2(&ground, ground_check[y][x], VECTOR2(x * Ground::size_X + 128, y * Ground::size_Y + 128));
					break;
				}
			}
		}
		groundManager()->add(&player_ground, VECTOR2(500, 500));
		uiManager()->init();
        //uiManager()->add(&ui_boss_start, VECTOR2(system::SCREEN_WIDTH - 200, 200));
		gameuiManager()->init();
		state++;
	case 1:      
		timer++;
		num = 0;
               
        bgManager()->update();
		playerManager()->update();      
        enemyManager()->update();     
		groundManager()->update();
		effectManager()->update();
		uiManager()->update();

        //チュートリアル
        switch (Game::Tutorial_State) 
		{
        case TUTORIAL_MOVE:
			Tutorial_move(false);
            break;

		case TUTORIAL_ATTACK:
			Tutorial_attack(false);
            break;

		case TUTORIAL_SPACE:
			Tutorial_space(false);
            break;

		case TUTORIAL_BOOM:
			Tutorial_boom(false);
            break;

		case TUTORIAL_LOCK:
			Tutorial_lock(false);
			break;

        case TUTORIAL_ENEMY:
			Tutorial_enemy(false);
            break;

        case MAINGAME://ボス
            MainGame();
            break;
        case GAME_WIN:
            if (TRG(0) & PAD_L3)
                changeScene(Title::instance());
            break;
        case GAME_LOSE:
            if (TRG(0) & PAD_L3)
                changeScene(Title::instance());
            break;
        }
        gameuiManager()->update();
		camera_update();        

		all_list.clear();
		for (auto& it : playerManager()->objList) { all_list.push_back(&it); }
		for (auto& it : enemyManager()->objList) { all_list.push_back(&it); }
		for (auto& it : effectManager()->objList) { all_list.push_back(&it); }
		all_judge_updata(all_list);
		break;
	}
}

bool drawlistsort(const OBJ2D* a, const OBJ2D* b) 
{
	if (a->distance == b->distance) { return a->position.x >= b->position.x; }
	return a->distance < b->distance;
}

void Game::draw()
{
	// 画面クリア
	GameLib::clear(VECTOR4(0, 0, 0, 1));
    bgManager()->draw();
	groundManager()->draw();
	all_list.sort(drawlistsort);
    for (auto& it : all_list) { it->draw_shadow(); }
	for (auto& it : all_list)
	{ 
		if (it->data == sprFireball) { GameLib::setBlendMode(Blender::BS_ADD); }
		if (it->data == sprAvoid) { GameLib::setBlendMode(Blender::BS_ADD); }
        it->draw();
        GameLib::setBlendMode(Blender::BS_ALPHA);
    }

	uiManager()->draw();
    gameuiManager()->draw();

    //チュートリアル
    switch (Tutorial_State) 
	{
	case TUTORIAL_MOVE:
		Tutorial_move(true);
        GameLib::sprite_render(sprMenu, 1920, 0, 1, 1, 0, 0, 414, 72, 414, 0, 0);
		break;
	case TUTORIAL_ATTACK:
		Tutorial_attack(true);
        GameLib::sprite_render(sprMenu, 1920, 0, 1, 1, 0, 0, 414, 72, 414, 0, 0);
		break;
	case TUTORIAL_SPACE:
		Tutorial_space(true);
        GameLib::sprite_render(sprMenu, 1920, 0, 1, 1, 0, 0, 414, 72, 414, 0, 0);
		break;
	case TUTORIAL_BOOM:
		Tutorial_boom(true);
        GameLib::sprite_render(sprMenu, 1920, 0, 1, 1, 0, 0, 414, 72, 414, 0, 0);
		break;
	case TUTORIAL_LOCK:
		Tutorial_lock(true);
        GameLib::sprite_render(sprMenu, 1920, 0, 1, 1, 0, 0, 414, 72, 414, 0, 0);
		break;
	case TUTORIAL_ENEMY:
		Tutorial_enemy(true);
        GameLib::sprite_render(sprMenu, 1920, 0, 1, 1, 0, 0, 414, 72, 414, 0, 0);
		break;

    case MAINGAME:
        GameLib::sprite_render(sprMenu, 1920, 0, 1, 1, 0, 0, 414, 72, 414, 0, 0);
        break;

    case GAME_WIN:    
        sprite_render2(sprClear, 0, 0, 1, 1, 0, 0, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
		break;
	case GAME_LOSE:
        sprite_render2(sprGameOver, 0, 0, 1, 1, 0, 0, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
        break;
    }

}

void Game::Tutorial_move(bool isDraw)
{
	if (!isDraw) 
	{
		switch (substate)
		{
		case 0:
			Tutorial_target= groundManager()->add(&tuto_move, VECTOR2(700, 700));
			Tutorial_mark = effectManager()->add(&tuto_target, Tutorial_target->position, 0, VECTOR2(0, 0));
			substate++;
			break;
		case 1:
			OBJ2D* PL = &playerManager()->objList.begin()._Ptr->_Myval;
			if (circleHitCheck(PL->position, PL->size, Tutorial_target->position, Tutorial_target->size))
			{
				Tutorial_target->clear();
				Tutorial_mark->clear();
                setTutorialState(TUTORIAL_ATTACK);
			}
			break;        
		}
	}
	else
	{
        sprite_render(sprTutorial, 0, 0, 1, 1, 0, 0, 1980, 300, 0, 0, 0);
	}
}
void Game::Tutorial_attack(bool isDraw)
{
    if (!isDraw)
    {
        switch (substate)
        {
        case 0:
            Tutorial_target = groundManager()->add(&tuto_move, VECTOR2(700, 200));
            Tutorial_mark = effectManager()->add(&tuto_target, Tutorial_target->position, 0, VECTOR2(0, 0));
            enemyManager()->add(&tutorialenemy, Tutorial_target->position);
            substate = 1;
            break;
        case 1:       
            if (enemyManager()->objList.empty()) 
			{
                Tutorial_target->clear();
                Tutorial_mark->clear();
                substate = 0;
                setTutorialState(TUTORIAL_SPACE);
            }
            break;
        }
    }
    else {
        sprite_render(sprTutorial, 0, 0, 1, 1, 0, 300, 1980, 300, 0, 0, 0);
    }
}
void Game::Tutorial_space(bool isDraw)
{
    if (!isDraw)
    {
        switch (substate)
        {
        case 0:           
            substate = 1;
            break;
        case 1:
            if (Player::skill2_timer == player.skill2->Casting_TIME - 1) 
			{
                Tutorial_Count++;
            }
            if (Tutorial_Count >= 1)
			{
                substate = 0;
                setTutorialState(TUTORIAL_BOOM);
            }
            break;
        }
    }
    else 
	{
        sprite_render(sprTutorial, 0, 0, 1, 1, 0, 300 * 2, 1980, 300, 0, 0, 0);
    }
}
void Game::Tutorial_boom(bool isDraw)
{
    if (!isDraw)
    {
        switch (substate)
        {
        case 0:
            Tutorial_Count = 0;
            substate = 1;
            break;
        case 1:
            if(Player::skill3_timer == player.skill3->Casting_TIME - 1)
			{
                Tutorial_Count++;
            }
            if (Tutorial_Count >= 1) 
			{
                Tutorial_Count = 0;
                substate = 2;
            }            
            break;
        case 2:         
            break;
        }
    }
    else {
        sprite_render(sprTutorial, 0, 0, 1, 1, 0, 300 * 3, 1980, 300, 0, 0, 0);
    }
}
void Game::Tutorial_lock(bool isDraw)
{
    if (!isDraw)
    {
        switch (substate)
        {
        case 0:
            Tutorial_target = groundManager()->add(&tuto_move, VECTOR2(700, 700));
            Tutorial_mark = effectManager()->add(&tuto_target, Tutorial_target->position, 0, VECTOR2(0, 0));
            enemyManager()->add(&tutorialenemy, Tutorial_target->position);
            substate = 1;
            break;
        case 1:
            break;
        case 2:           
            break;
        }
    }
    else
	{
        if (substate == 1) 
		{
            sprite_render(sprTutorial, 0, 0, 1, 1, 0, 300 * 4, 1980, 300, 0, 0, 0);
        }
        else
		{
            sprite_render(sprTutorial, 0, 0, 1, 1, 0, 300 * 5, 1980, 300, 0, 0, 0);
        }
    }
}
void Game::Tutorial_enemy(bool isDraw)
{
    if (!isDraw)
    {
        switch (substate)
        {
        case 0:          
            enemyManager()->add(&enemy2, VECTOR2(700,700));
            substate = 1;
            break;

        case 1:
            if (enemyManager()->objList.empty()) 
			{
                substate = 0;
                setTutorialState(MAINGAME);
            }
            break;
        }
    }
    else 
	{
        sprite_render(sprTutorial, 0, 0, 1, 1, 0, 300 * 6, 1980, 300, 0, 0, 0);
    }
}
void Game::MainGame()
{  
	switch (substate)
    {
    case 0:
        Game::instance()->enemyManager()->objList.clear();
        Game::instance()->uiManager()->UI_List.clear();
        Game::instance()->gameuiManager()->objList.clear();
        playerManager()->init();
        camera_pos_target1 = nullptr;
        camera_pos_target2 = nullptr;
        playerManager()->add(&player, VECTOR2(1700, 1700));
        Game::instance()->enemyManager()->add(&boss, VECTOR2(400, 400));
        camera_angle = 45;
        substate = 1;
        break;
    case 1:       
        if (Game::instance()->enemyManager()->objList.empty()) 
        {
            playerManager()->objList.clear();
            Game::setTutorialState(Game::TUTORIAL_STATE::GAME_WIN);
        }
        else if (Game::instance()->playerManager()->objList.empty()) 
        {
            enemyManager()->objList.clear();
            Game::setTutorialState(Game::TUTORIAL_STATE::GAME_LOSE);
        }
        break;
    }
}

void Game::uninit()
{
	all_list.clear();
	safe_delete(playerManager_);
	safe_delete(enemyManager_);
	safe_delete(groundManager_);
	safe_delete(effectManager_);
	safe_delete(uiManager_);
	safe_delete(gameuiManager_);
	music::clear();
}

void all_judge_updata(std::list<OBJ2D*> list)
{
	std::list<OBJ2D*>::iterator a, b;

	for (a = list.begin(); a != list.end(); ++a)
	{	
        if (a._Ptr->_Myval->type == tNOTHING)continue;
        if (a == list.end())break;
        for (b = a; b != list.end(); ++b)
        {
            if (a == b)continue;
            if (a._Ptr->_Myval->type == b._Ptr->_Myval->type)
            {
                if (!(a._Ptr->_Myval->type == tENEMY2 && b._Ptr->_Myval->type == tENEMY2)) continue;
            }
            if (b._Ptr->_Myval->type == tNOTHING)continue;
            num++;

				if (a._Ptr->_Myval->type == tWall)
				{
					if (SquareHitCheck(
						a._Ptr->_Myval->is3Dposition[0], a._Ptr->_Myval->is3Dposition[1],
						a._Ptr->_Myval->is3Dposition[2], a._Ptr->_Myval->is3Dposition[3],
						b._Ptr->_Myval->position, b._Ptr->_Myval->size))
					{
						for (int i = 0; i < 4; i++) 
						{
							if (b._Ptr->_Myval->judgeFlag[i])continue;
							b._Ptr->_Myval->judgeFlag[i] = a._Ptr->_Myval;
							break;
						}
					}
				}
				else if(b._Ptr->_Myval->type == tWall)
				{
					if (SquareHitCheck(
						b._Ptr->_Myval->is3Dposition[0], b._Ptr->_Myval->is3Dposition[1],
						b._Ptr->_Myval->is3Dposition[2], b._Ptr->_Myval->is3Dposition[3],
						a._Ptr->_Myval->position, a._Ptr->_Myval->size))
					{
						for (int i = 0; i < 4; i++) 
						{
							if (a._Ptr->_Myval->judgeFlag[i])continue;
							a._Ptr->_Myval->judgeFlag[i] = b._Ptr->_Myval;
							break;
						}
					}
				}                
                else
                {
                    if (circleHitCheck(a._Ptr->_Myval->position, a._Ptr->_Myval->size, b._Ptr->_Myval->position, b._Ptr->_Myval->size))
                    {
                        for (int i = 0; i < 4; i++)
						{
                            if (b._Ptr->_Myval->judgeFlag[i])continue;
                            b._Ptr->_Myval->judgeFlag[i] = a._Ptr->_Myval;
                            break;
                        }
                        for (int i = 0; i < 4; i++) 
						{
                            if (a._Ptr->_Myval->judgeFlag[i])continue;
                            a._Ptr->_Myval->judgeFlag[i] = b._Ptr->_Myval;
                            break;
                        }
                    }
                }
			}
	}
}