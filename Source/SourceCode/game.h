#ifndef INCLUDED_GAME
#define	INCLUDED_GAME

class Game : public Scene
{
public:
    std::list<OBJ2D*> all_list;
   
    static Game* instance() { return &instance_; }
    static int Tutorial_State;
    static int Tutorial_Count;
	static float Tutorial_fWork;

	OBJ2D* Tutorial_target = nullptr;
	OBJ2D* Tutorial_mark = nullptr;
    int substate;
	int pauseState;

    void init();
    void update();
    void draw();
    void uninit();

	enum TUTORIAL_STATE
	{
		TUTORIAL_MOVE,
		TUTORIAL_ATTACK,
		TUTORIAL_SPACE,
		TUTORIAL_BOOM,
		TUTORIAL_LOCK,
		TUTORIAL_ENEMY,
		MAINGAME,
		GAME_WIN,
		GAME_LOSE,
	};
	void setTutorialState(int num)
	{
		Tutorial_target = nullptr;
		Tutorial_mark = nullptr;
		Tutorial_State = num;
		Tutorial_Count = 0;
		substate = 0;
	}

    BGManager*          bgManager() { return bgManager_; }
    PlayerManager*      playerManager() { return playerManager_; }
    EnemyManager*       enemyManager() { return enemyManager_; }
    GroundManager*      groundManager() { return groundManager_; }
    EffectManager*      effectManager() { return effectManager_; }
	UIManager*			uiManager()     { return uiManager_; }
    GameUIManager*      gameuiManager() { return gameuiManager_; }

public:
    bool                isPaused;
private:
    BGManager*          bgManager_;
    PlayerManager*      playerManager_;
    EnemyManager*       enemyManager_;
    GroundManager*      groundManager_;
    EffectManager*      effectManager_;
	UIManager*			uiManager_;
    GameUIManager*      gameuiManager_;

    static Game instance_;

	void Tutorial_move(bool isDraw);
	void Tutorial_attack(bool isDraw);
	void Tutorial_space(bool isDraw);
	void Tutorial_boom(bool isDraw);
	void Tutorial_lock(bool isDraw);
	void Tutorial_enemy(bool isDraw);
    void MainGame();
};
#endif // !INCLUDED_GAME
