#pragma once

class EffectManager : public OBJ2DManager
{
public:
    OBJ2D* add(MoveAlg* skillAlg, const VECTOR2& pos,int atk, VECTOR2 vec);

public:
    //void init();    // ‰Šú‰»
    void update();  // XV
    //void draw();    // •`‰æ
};