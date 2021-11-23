#pragma warning(disable:4100)
#include "all.h"

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    SceneManager sceneManager;
    sceneManager.execute(Title::instance());

    return 0;
}
