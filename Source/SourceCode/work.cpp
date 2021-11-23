#define WORK
#include "all.h"
VECTOR2 NorVector(VECTOR2 a, VECTOR2 b) 
{
    VECTOR2 t;
    t.x = a.x - b.x;
    t.y = (a.y - b.y);

    float l;
	l = sqrtf((t.x*t.x) + (t.y*t.y));
	if (l) 
	{
		t.x /= l;
		t.y /= l;
		return VECTOR2(t.x, t.y);
	}
	else { return VECTOR2(1, 1); } 
}
VECTOR2 NorVector(VECTOR2 a)
{
    return NorVector(a, VECTOR2(0, 0));
}

VECTOR2 VecRotation(VECTOR2 a, float b)
{
    VECTOR2 temppos = a;
    a.x = temppos.x*cosf(ToRadian(b)) - temppos.y*sinf(ToRadian(b));
    a.y = temppos.x*sinf(ToRadian(b)) + temppos.y*cosf(ToRadian(b));
    return a;
}
//“–‚½‚è”»’è
bool hit_check(VECTOR2 a, VECTOR2 b, float sum_radius) 
{
	float distance = sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	if (sum_radius >= distance) { return true; }
	return false;
}

//ƒGƒŠƒA“à”»’è
bool areaCheck(VECTOR2 obj, int x1, int y1, int x2, int y2)
{
    if (obj.x < x1 ||
        obj.x > x2 ||
        obj.y < y1 ||
        obj.y > y2)
    {
        return false;
    }
    return true;
}