#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

class Player : public MoveAlg 
{
public:
    static int skill1_timer;
    static int skill2_timer;
    static int skill3_timer;

    SkillAlg* skill1;
    SkillAlg* skill2;
    SkillAlg* skill3;

    float rockon_angle;
    OBJ2D* lock_target;

    VECTOR2 temp;

public:
	void move(OBJ2D* obj);
    void move_update(OBJ2D*obj);
    void pos_update(OBJ2D*obj);
    void skill_update(OBJ2D* obj);
    void animation_update(OBJ2D* obj);
};
EXTERN Player player;


class PlayerManager : public OBJ2DManager
{
public:
    static constexpr float PLAYER_MOVE = 6.0f;

public:   
    //void init();    // èâä˙âª
    void update();  // çXêV
    //void draw();    // ï`âÊ
};

class Player_Ground :public MoveAlg
{
public:
	void move(OBJ2D* obj);
};

EXTERN Player_Ground player_ground;

#endif // !INCLUDED_PLAYER
