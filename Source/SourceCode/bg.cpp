#include"all.h"

void BG::move(OBJ2D *obj)
{
    switch (obj->state)
    {
    case 0:   
        obj->data = sprBg;
        obj->position = VECTOR2(0, 0);
        obj->scale = VECTOR2(1, camera_scale_y);
        obj->texPos = VECTOR2(0, 0);
        obj->texSize = VECTOR2(3000, 3000);
        obj->texPivot = VECTOR2(1500, 1500);
        obj->color = VECTOR4(1, 1, 1, 1);
        obj->size = obj->texSize.x / 4;
        obj->timer = 0;
        obj->state++;
        break;

    case 1:       
        obj->position = Game::instance()->playerManager()->objList.begin()->position;
        obj->position *= 0.7;
        obj->angle = ToRadian(camera_angle);
        break;
    }
}

