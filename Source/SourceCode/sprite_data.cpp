//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;
using namespace audio;
//------< データ >---------------------------------------------------------------

GameLib::Sprite* sprtutorial_move;
GameLib::Sprite* sprtutorial_target;
//------< Player >----------------------------------------------------------
GameLib::Sprite* sprPlayer;
GameLib::Sprite* sprPlayer_Ground;
GameLib::Sprite* sprFireball;
GameLib::Sprite* sprBomb;
GameLib::Sprite* sprAvoid;
GameLib::Sprite* sprPlayer_hp;
GameLib::Sprite* sprPlayer_wave_hp;
GameLib::Sprite* sprPlayer_skill;
GameLib::Sprite* sprPlayer_skill1;
GameLib::Sprite* sprPlayer_skill2;
GameLib::Sprite* sprPlayer_skill3;
//------< Enemy >----------------------------------------------------------
GameLib::Sprite* sprEnemy;//BOSS
GameLib::Sprite* sprBoss_Shot;
GameLib::Sprite* sprBoss_Ground;
GameLib::Sprite* sprBoss_Skill_Ground;
GameLib::Sprite* sprBoss_hp;

GameLib::Sprite* sprEnemy1;//雑魚
GameLib::Sprite* sprEnemy_hp;
GameLib::Sprite* sprEnemy_Shot;

//------< Ground >----------------------------------------------------------
GameLib::Sprite* sprGround;
GameLib::Sprite* sprGround2;
//------< Bg >----------------------------------------------------------
GameLib::Sprite* sprBg;
GameLib::Sprite* sprTitle_Bg;
//------< UI >----------------------------------------------------------
GameLib::Sprite* sprMouse;
GameLib::Sprite* spruiStart;
GameLib::Sprite* sprShadow;
GameLib::Sprite* sprSkill_full;
GameLib::Sprite* sprTutorial;
GameLib::Sprite* sprClear;
GameLib::Sprite* sprGameOver;
GameLib::Sprite* sprBoss_skip;

GameLib::Sprite* spruiTitle;
GameLib::Sprite* spruiGame;
GameLib::Sprite* sprMenu;

//------------------------------------------------------------------------------


void sprite_load()
{
	sprite_load(&sprtutorial_move, L"./Data/Images/bg/tutorial_move.png");
	sprite_load(&sprtutorial_target, L"./Data/Images/bg/tutorial_target.png");

	sprite_load(&sprPlayer, L"./Data/Images/player/player.png");
	sprite_load(&sprPlayer_Ground, L"./Data/Images/player/player_ground.png");
	sprite_load(&sprFireball, L"./Data/Images/player/fireball.png");
    sprite_load(&sprBomb, L"./Data/Images/player/bomb.png");
    sprite_load(&sprAvoid, L"./Data/Images/player/light.png");

	sprite_load(&sprEnemy, L"./Data/Images/enemy/boss.png");
    sprite_load(&sprEnemy1, L"./Data/Images/enemy/enemy1.png");

    sprite_load(&sprBoss_Shot, L"./Data/Images/enemy/boss_shot_all.png");
	sprite_load(&sprBoss_Ground, L"./Data/Images/enemy/boss_ground.png");
	sprite_load(&sprBoss_Skill_Ground, L"./Data/Images/enemy/boss_skill_ground.png");
	
	sprite_load(&sprGround, L"./Data/Images/bg/ground.png");
	sprite_load(&sprGround2, L"./Data/Images/bg/ground2.png");
    sprite_load(&sprBg, L"./Data/Images/bg/bg.png");

	sprite_load(&sprTitle_Bg, L"./Data/Images/bg/title_bg.png");

	sprite_load(&spruiStart, L"./Data/Images/ui/start.png");
	sprite_load(&sprMouse, L"./Data/Images/ui/mouse.png");
    sprite_load(&sprEnemy_hp, L"./Data/Images/ui/enemy_hp.png");
    sprite_load(&sprBoss_hp, L"./Data/Images/ui/boss_hp.png");
    sprite_load(&sprPlayer_hp, L"./Data/Images/ui/player_hp.png");
    sprite_load(&sprPlayer_wave_hp, L"./Data/Images/ui/player_wave_hp.png");
    sprite_load(&sprPlayer_skill, L"./Data/Images/ui/skill_bar.png");
    sprite_load(&sprPlayer_skill1, L"./Data/Images/ui/fireball_skill_ui.png");
    sprite_load(&sprPlayer_skill2, L"./Data/Images/ui/Avoidance.png");
    sprite_load(&sprPlayer_skill3, L"./Data/Images/ui/lock_ui.png");
    sprite_load(&sprShadow, L"./Data/Images/ui/shadow.png");
    sprite_load(&sprSkill_full, L"./Data/Images/ui/skill_bar_lighting.png");
    sprite_load(&sprTutorial, L"./Data/Images/ui/tutorial.png");
    sprite_load(&sprClear, L"./Data/Images/ui/PlayerWin.png");
    sprite_load(&sprGameOver, L"./Data/Images/ui/BossWin.png");
    sprite_load(&sprBoss_skip, L"./Data/Images/ui/boss_skip.png");

	sprite_load(&spruiTitle, L"./Data/Images/ui/titlebuttom.png");
	sprite_load(&spruiGame, L"./Data/Images/ui/backbuttom.png");
	sprite_load(&sprMenu, L"./Data/Images/ui/menu.png");
}

void sound_load()
{	
	sound::load(L"./Data/Sounds/sounds.xwb");
}
void music_load()
{
	music::load(0, L"./Data/Musics/bgm.wav",0.3f);
}
//******************************************************************************
