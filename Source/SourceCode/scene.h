#ifndef INCLUDED_SCENE
#define INCLUDED_SCENE

extern VECTOR2 mousePos;

class Scene
{
protected:
    int state;          // ���
    int timer;          // �^�C�}�[
    Scene* nextScene;   // ���̃V�[��

public:
    Scene* execute();   // ���s����

    virtual void init()
    { 
        state = 0;
        timer = 0;
        nextScene = nullptr;
    };
    virtual void uninit() {};   // �I������
    virtual void update() {};   // �X�V����
    virtual void draw()   {};   // �`�揈��

    void changeScene(Scene *scene) { nextScene = scene; }   // �V�[���ύX����
    Scene *getScene() const { return nextScene; }           // nextScene�̃Q�b�^�[
};

class SceneManager
{
public:
    void execute(Scene*);  // ���s����
};


#endif // !INCLUDED_SCENE