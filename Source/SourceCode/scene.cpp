#include "all.h"

VECTOR2 mousePos;

Scene* Scene::execute()
{
    using namespace GameLib;

    init();
    while (GameLib::gameLoop(false))    
    {
        input::update();
		mousePos.x = float(input::getCursorPosX());
		mousePos.y = float(input::getCursorPosY());

        update();
        draw();
		sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 30, 30, 0, 0, 0, 1, 1, 1, 1);
        debug::display(1, 1, 1, 1, 1);
        GameLib::present(1, 0);
		if (nextScene) { break; }
    }
    uninit();
    return nextScene;	
}

void SceneManager::execute(Scene* scene)
{
    using namespace GameLib;
    bool isFullScreen = true;	// フルスクリーンにするならtrueに変える
                               
    // ゲームライブラリの初期化処理
    GameLib::init(L"BOOM", 
        static_cast<int>(system::SCREEN_WIDTH), 
        static_cast<int>(system::SCREEN_HEIGHT), 
        isFullScreen);

#ifndef _DEBUG
    ShowCursor(!isFullScreen);	// フルスクリーン時はカーソルを消す
#endif
	sprite_load();
    while (scene)
    {
        scene = scene->execute();
    }

    GameLib::uninit();
}

