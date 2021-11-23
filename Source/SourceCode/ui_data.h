#ifndef INCLUDED_UI_DATA
#define INCLUDED_UI_DATA

class UI_START :public UI_Alg
{
	void init(OBJ_UI*);
	//void touch_updata(OBJ_UI*);
	void click_updata(OBJ_UI*);
};
EXTERN UI_START ui_start;

class UI_BOSS_START :public UI_Alg
{
    void init(OBJ_UI*);
    //void touch_updata(OBJ_UI*);
    void click_updata(OBJ_UI*);
};
EXTERN UI_BOSS_START ui_boss_start;

class UI_TITLE :public UI_Alg
{
	void init(OBJ_UI*);
	void click_updata(OBJ_UI*);
};
EXTERN UI_TITLE ui_title;

class UI_GAME :public UI_Alg
{
	void init(OBJ_UI*);
	void click_updata(OBJ_UI*);
};
EXTERN UI_GAME ui_game;

class TUTO_MOVE :public MoveAlg
{
public:
	void move(OBJ2D* obj);
};
EXTERN TUTO_MOVE tuto_move;

class TUTO_TARGET :public MoveAlg
{
public:
	void move(OBJ2D* obj);
};
EXTERN TUTO_TARGET tuto_target;

#endif // !INCLUDED_UI_DATA