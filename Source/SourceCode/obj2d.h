#ifndef INCLUDED_OBJ2D
#define	INCLUDED_OBJ2D

#include <list>
#include "../GameLib/vector.h"
#include "../GameLib/obj2d_data.h"

class OBJ2D;

class MoveAlg
{
public:
    virtual void move(OBJ2D* obj) = 0;  
};


class EraseAlg
{
public:
    virtual void erase(OBJ2D* obj) = 0; 
};

enum obj_type
{
	tNOTHING,
	tPLAYER,
	tENEMY,
	tENEMY2,
	tGROUND,
	tWall,
	tENEMY_SKILL,//相殺
    tFIREBALL,
    tBOMB_FIREBALL,
    tBOMB,
	tENEMY_GROUND,
	tENEMY_SKILL2,//プレイヤー強
	tENEMY_SKILL3,//敵強
	tENEMY_SKILL4,//雨
	tSHADOW,
};


class OBJ2D
{
public:
    // メンバ変数
	BOOL                    exist;				// 存在
	int                     type;				// タイプ
	float                   hp;

	GameLib::Sprite*		data;				// スプライトデータ
	VECTOR2 				anime;				// アニメーションクラス
    VECTOR2                 position;           // 位置
	VECTOR2					is3Dposition[4];    // (四角)位置

	// 描画用変数
	VECTOR2					pos;				// 描画位置
    VECTOR2                 scale;              // スケール
	VECTOR2					draw_scale;
	VECTOR2					texPos;				// 元画像位置
	VECTOR2					texSize;			// 元画像大きさ
	VECTOR2					texPivot;			// 基準点の位置
	float					height;
    float                   angle;              // 角度
    VECTOR4                 color;              // 描画色
	float					distance;			// 描画後Y軸(1080)との距離
	float					sideMove;
	bool					isDraw3D;			// 3Dの描画
	float					is3DSize;           // 高さ
	VECTOR2					is3Dpos[4];			// (四角)描画位置

	//更新用
    MoveAlg*                mvAlg;              // 移動アルゴリズム
	int						move_pattern;
	int                     state;              // ステート
	int                     timer;              // タイマー

	float                   size;               // あたり用サイズ（半径）
    float                   velocity;           // 速度
    VECTOR2                 speed;              // 瞬間の移動量ベクト
	int						invincible_timer;	// 無敵状態	

	OBJ2D*	                judgeFlag[4];          // あたり判定（対象を返す）
	VECTOR2                 nock_back;			// ノックバック移動量

    OBJ2D*                  P;                  //(対象を返す)
    bool                    screen_drow;        //(カメラに干渉しない)

    BYTE                    pad[1];             // 1バイトの空き
public:

    OBJ2D();        // コンストラクタ
    void clear();   // メンバ変数のクリア
    void move();    // 移動
    void draw();    // 描画
    void draw_shadow();
    void Wall_check(int i);
	void obj_check(int i);
    void area_check();
};


class OBJ2DManager 
{
protected:
public:
    std::list<OBJ2D>  objList; 
public:
    // デストラクタ
    ~OBJ2DManager();

    void init();    // 初期化
    void update();  // 更新
    void draw();    // 描画

    OBJ2D* add(MoveAlg* mvAlg, const VECTOR2& pos = VECTOR2(0, 0)); // objListに新たなOBJ2Dを追加する
    VECTOR2 get_position(OBJ2D a) { return a.position; }
    std::list<OBJ2D>* getList() { return &objList; }                // objListを取得する
};
#endif// ! INCLUDED_OBJ2D