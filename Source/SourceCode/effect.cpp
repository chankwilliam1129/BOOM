#include "all.h"

OBJ2D* EffectManager::add(MoveAlg* mvAlg, const VECTOR2& pos,int move_pattern,VECTOR2 vec)
{
    OBJ2D obj;                          
    obj.move_pattern = move_pattern;
    obj.speed = vec;
    obj.mvAlg = mvAlg;                  
    obj.position = pos;                 
    obj.scale = VECTOR2(1, 1);          
    obj.color = VECTOR4(1, 1, 1, 1);    

    objList.push_back(obj);             
    return &(*objList.rbegin());        
}

void EffectManager::update() 
{
	int num = 0;
    for (auto& it : objList) 
    {
        it.move();
        draw_pos_update(&it);
		num++;
    }
	objList.remove_if([](OBJ2D i) {return !(i.exist); });
}