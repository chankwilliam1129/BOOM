#ifndef INCLUDED_ENEMY
#define INCLUDED_ENEMY

class TutorialEnemy : public MoveAlg
{
public:

    void move(OBJ2D* obj);
    void animation_update(OBJ2D*obj);
};

EXTERN TutorialEnemy tutorialenemy;

class Enemy : public MoveAlg
{
public:
	struct Move_Pattern
	{
		int state;
		int timer;
		int pattern;
		VECTOR2 pl_pos;
	};
    const float HP = 100;
	Move_Pattern move_pt[2];

	void move(OBJ2D* obj);
	void pattern_update(OBJ2D* obj, Move_Pattern* m);

	void pattern01(OBJ2D* obj, Move_Pattern* m);
	void pattern02(OBJ2D* obj, Move_Pattern* m);
	void pattern03(OBJ2D* obj, Move_Pattern* m);
	void pattern04(OBJ2D* obj, Move_Pattern* m);
	void pattern05(OBJ2D* obj, Move_Pattern* m);
	void pattern06(OBJ2D* obj, Move_Pattern* m);
	void animation_update(OBJ2D*obj);
};

EXTERN Enemy boss;

class Enemy2 : public MoveAlg
{
public:
	struct Move_Pattern
	{
		int state;
		int timer;
		int pattern;
		VECTOR2 pl_pos;
	};

	Move_Pattern move_pt[2];

	void move(OBJ2D* obj);
	void pattern_update(OBJ2D* obj, Move_Pattern* m);

	void pattern01(OBJ2D* obj, Move_Pattern* m);
	void pattern02(OBJ2D* obj, Move_Pattern* m);
	static const int num = 3;
	int count = 0;
	void animation_update(OBJ2D*obj);
};

EXTERN Enemy2 enemy2;

class Enemy_Ground :public MoveAlg 
{
public:
	void move(OBJ2D* obj);
};

EXTERN Enemy_Ground enemy_ground;

class Enemy_Ground2 :public MoveAlg
{
public:
	void move(OBJ2D* obj);
};

EXTERN Enemy_Ground2 enemy_ground2;

class Enemy_Ground3 :public MoveAlg 
{
public:
	void move(OBJ2D* obj);
};

EXTERN Enemy_Ground3 enemy_ground3;

class Enemy_Ground4 :public MoveAlg 
{
public:
	void move(OBJ2D* obj);
};

EXTERN Enemy_Ground4 enemy_ground4;

class Enemy_Ground5 :public MoveAlg 
{
public:
	void move(OBJ2D* obj);
};
EXTERN Enemy_Ground5 enemy_ground5;

class EnemyManager : public OBJ2DManager
{
public:
	static constexpr float ENEMY_MOVE = 4.0f;

public:
	//void init();    // èâä˙âª
	//void update();  // çXêV
	//void draw();    // ï`âÊ
};
#endif // !INCLUDED_ENEMY


