#ifndef INCLUDED_JUDGE
#define INCLUDED_JUDGE

float vector2LengthSq(VECTOR2);
float vector2Length(VECTOR2);
float Length(VECTOR2 a, VECTOR2 b);
float cross(VECTOR2 a, VECTOR2 b, VECTOR2 p);

BOOL circleHitCheck(VECTOR2 v1, float r1, VECTOR2 v2, float r2);
BOOL SquareHitCheck(VECTOR2 v1, VECTOR2 v2, VECTOR2 v3, VECTOR2 v4, VECTOR2 t, float r);
BOOL SquareHitCheck(VECTOR2 v[4], VECTOR2 t, float r);

#endif // !INCLUDED_JUDGE
