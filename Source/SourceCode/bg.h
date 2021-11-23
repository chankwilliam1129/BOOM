#pragma once

class BG :public MoveAlg
{
public:
    static const int size_X = 3000;
    static const int size_Y = 3000;

public:
    void move(OBJ2D *obj);
};

class BGManager :public OBJ2DManager 
{
};
EXTERN BG bg;