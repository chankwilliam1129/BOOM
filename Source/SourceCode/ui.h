#ifndef INCLUDED_UI
#define INCLUDED_UI

#include <list>
#include "../GameLib/vector.h"
#include "../GameLib/obj2d_data.h"
#include "../GameLib/input_manager.h"

class UI_Alg;

class OBJ_UI
{
public:
	GameLib::Sprite*		data;
	bool					circle;
	VECTOR2					pos;				// 描画位置
	VECTOR2                 scale;              // スケール
	VECTOR2					texPos;				// 元画像位置
	VECTOR2					texSize;			// 元画像大きさ
	VECTOR2					texPivot;			// 基準点の位置
	float                   angle;              // 角度
	VECTOR4                 color;              // 描画色
	VECTOR2                 size;               // あたり用サイズ（縦横）
	int						anime;
	int						state;
	int						click;
	UI_Alg*					uiAlg;

public:
	void init();
	void draw();
};

class UI_Alg
{
public:
    virtual void init(OBJ_UI*) {};
    virtual void touch_updata(OBJ_UI*) {};
    virtual void click_updata(OBJ_UI*) {};
};

class UIManager
{
public:
    std::list<OBJ_UI>  UI_List;

	~UIManager();

	void init();		// 初期化
	void update();		// 更新
	void draw();		// 描画

	OBJ_UI* add(UI_Alg* uiAlg, const VECTOR2& pos = VECTOR2(0, 0)); 
	std::list<OBJ_UI>* getList() { return &UI_List; }                

};


class GameUIManager :public OBJ2DManager
{
public:
    OBJ2D* ui_add(MoveAlg* mvAlg, const VECTOR2& pos, int type, OBJ2D*p);
    void update();  // 更新
    void draw();    // 描画
};

class HP : public MoveAlg
{
public:
    void move(OBJ2D* obj);
};
EXTERN HP hp;

class Skill : public MoveAlg 
{
public:
    void move(OBJ2D* obj);
};
EXTERN Skill skill;

class UI_FULL : public MoveAlg 
{
public:
    int state;
public:
    void move(OBJ2D* obj);
};
EXTERN UI_FULL ui_full;

class CLEAR : public MoveAlg
{
public:
    void move(OBJ2D* obj);
};
EXTERN CLEAR clear;
#endif // !INCLUDED_UI