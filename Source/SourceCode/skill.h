#pragma once

class SkillAlg 
{
public:
    int CoolDown_TIME = 0;
    int Casting_TIME = 0;
    VECTOR2 vec;

public:
    virtual void use(OBJ2D* obj,int,VECTOR2) = 0;
    BOOL areaCheck(OBJ2D* obj, float limit);
};

//PLAYER
class Fire : public SkillAlg
{
public:
    Fire()
    {
        CoolDown_TIME = 50;
        Casting_TIME = 32;
    }
public:
	void use(OBJ2D* obj, int, VECTOR2);
};
class FireBall :public MoveAlg
{
public:
    void move(OBJ2D* obj);
};
EXTERN FireBall fireball;

class BombFireBall :public MoveAlg
{
public:
    void move(OBJ2D* obj);
};
EXTERN BombFireBall bombfireball;

class Avoid :public SkillAlg
{
public:
    OBJ2D* p;
    Avoid()
	{
        CoolDown_TIME = 50;
        Casting_TIME = 40;
    }
public:
    void use(OBJ2D* obj, int, VECTOR2);
};

class Avoid_Move :public MoveAlg 
{
public:
    OBJ2D* p;
public:
    void move(OBJ2D* obj);
};
EXTERN Avoid_Move avoid_move;

class BOMB_SET :public SkillAlg
{
public:
    static bool areaflg;
public:
    BOMB_SET() 
	{
        CoolDown_TIME = 5;
        Casting_TIME = 5;
    }
public:
    void use(OBJ2D* obj, int, VECTOR2);
};
class BOMB :public MoveAlg 
{
public:
    void move(OBJ2D* obj);
};
EXTERN BOMB bomb;

//BOSS
class BossNomalBall :public MoveAlg
{
public:
	void move(OBJ2D* obj);
};
EXTERN BossNomalBall bossnomalball;

class BossFireBall :public MoveAlg
{
public:
	void move(OBJ2D* obj);
};
EXTERN BossFireBall bossfireball;

class BossTeleport :public MoveAlg
{
public:
	void move(OBJ2D* obj);
};
EXTERN BossTeleport bossteleport;


class BossPursuitBall :public MoveAlg
{
public:
	void move(OBJ2D*obj);
};
EXTERN BossPursuitBall bosspursuitball;

class BossRain :public MoveAlg
{
public:
	void move(OBJ2D*obj);
};
EXTERN BossRain bossrain;

//ŽG‹›
class ZakoNomalBall :public MoveAlg
{
public:
	void move(OBJ2D*obj);
};
EXTERN ZakoNomalBall zakonomalball;