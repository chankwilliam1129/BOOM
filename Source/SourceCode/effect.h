#pragma once

class EffectManager : public OBJ2DManager
{
public:
    OBJ2D* add(MoveAlg* skillAlg, const VECTOR2& pos,int atk, VECTOR2 vec);

public:
    //void init();    // 初期化
    void update();  // 更新
    //void draw();    // 描画
};