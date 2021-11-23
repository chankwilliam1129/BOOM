
class Ground : public MoveAlg
{
public:
    static const int size_X = 256;
    static const int size_Y = 256;
    static  const int height = 10;
    static const int width = 10;
    void move(OBJ2D* obj);
};
EXTERN Ground ground;

extern int ground_check[Ground::height][Ground::width];

class Pillar :public MoveAlg
{
public:
	void move(OBJ2D* obj);
};
EXTERN Pillar pillar;

class GroundManager : public OBJ2DManager
{
public:
    OBJ2D* add2(MoveAlg* mvAlg, int, const VECTOR2& pos = VECTOR2(0, 0));
    //void init() 
    //void update();  // çXêV
    void draw();    // ï`âÊ
};