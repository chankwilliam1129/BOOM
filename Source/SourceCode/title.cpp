#include "all.h"

using namespace GameLib;

Title Title::instance_;

void Title::init()
{
	Scene::init();	    
	uiManager_ = new UIManager;
	music_load();
}

void Title::update()
{
	using namespace input;
	
	switch (state)
	{
	case 0:	
        music::play(0, true);
		timer = 0;                                 
		GameLib::setBlendMode(Blender::BS_ALPHA);   

		uiManager()->init();
		uiManager()->add(&ui_start, VECTOR2(system::SCREEN_WIDTH/2, system::SCREEN_HEIGHT/2));
        uiManager()->add(&ui_boss_start, VECTOR2(system::SCREEN_WIDTH-400, 200));
		state++;

	case 1:
		timer++;
		uiManager()->update();
		break;
	}
}

void Title::draw()
{
	GameLib::clear(VECTOR4(0, 0, 0, 1));	
	sprite_render(sprTitle_Bg, 0, 0, 1, 1, 0, 0, system::SCREEN_WIDTH, system::SCREEN_HEIGHT, 0, 0, 0, 1, 1, 1, 1);
	uiManager()->draw();
}

