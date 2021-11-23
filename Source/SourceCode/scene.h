#ifndef INCLUDED_SCENE
#define INCLUDED_SCENE

extern VECTOR2 mousePos;

class Scene
{
protected:
    int state;          // 状態
    int timer;          // タイマー
    Scene* nextScene;   // 次のシーン

public:
    Scene* execute();   // 実行処理

    virtual void init()
    { 
        state = 0;
        timer = 0;
        nextScene = nullptr;
    };
    virtual void uninit() {};   // 終了処理
    virtual void update() {};   // 更新処理
    virtual void draw()   {};   // 描画処理

    void changeScene(Scene *scene) { nextScene = scene; }   // シーン変更処理
    Scene *getScene() const { return nextScene; }           // nextSceneのゲッター
};

class SceneManager
{
public:
    void execute(Scene*);  // 実行処理
};


#endif // !INCLUDED_SCENE
