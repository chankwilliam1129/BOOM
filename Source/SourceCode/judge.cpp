#include "all.h"
//--------------------------------
//  ベクトルの長さの2乗を返す
//--------------------------------
float vector2LengthSq(VECTOR2 v)
{
    return v.x * v.x + v.y * v.y;
}

//--------------------------------
//  ベクトルの長さを返す
//--------------------------------
float vector2Length(VECTOR2 v)
{
    return sqrtf(vector2LengthSq(v));
}

//--------------------------------
// ベクトル引き算(a-b)
//--------------------------------
VECTOR2 sub_vector(VECTOR2 a, VECTOR2 b)
{
	VECTOR2 ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return ret;
}

//--------------------------------
// 長さを計算
//--------------------------------
float Length(VECTOR2 a, VECTOR2 b)
{
	return vector2Length(sub_vector(a, b));
}

//--------------------------------
// 内積 dot		(AP.AB)
//--------------------------------
float dot(VECTOR2 a, VECTOR2 b ,VECTOR2 p) 
{
	VECTOR2 ap = sub_vector(a, p);
	VECTOR2 ab = sub_vector(a, b);

	return(ab.x*ap.x + ab.y*ap.y);
}

//--------------------------------
// 内積 dot2	(BP.AB)
//--------------------------------
float dot2(VECTOR2 a, VECTOR2 b, VECTOR2 p)
{
	VECTOR2 bp = sub_vector(b, p);
	VECTOR2 ab = sub_vector(a, b);

	return(bp.x*ab.x + bp.y*ab.y);
}

//--------------------------------
// 外積 cross	(AB*AP)
//--------------------------------
float cross(VECTOR2 a, VECTOR2 b, VECTOR2 p)
{
	VECTOR2 ab = sub_vector(a, b);
	VECTOR2 ap = sub_vector(a, p);

	return (ab.x*ap.y - ab.y*ap.x);
}

//--------------------------------
//  あたり判定（円）
//--------------------------------
BOOL circleHitCheck(VECTOR2 v1, float r1, VECTOR2 v2, float r2)
{
    VECTOR2 v = v2 - v1;
    float lenSq = vector2LengthSq(v);
	if (lenSq <= (r1 + r2) * (r1 + r2))
	{
		return TRUE;
	}
    return FALSE;
}

//--------------------------------
//  あたり判定（レーザー）
//--------------------------------
BOOL LaserHitCheck( VECTOR2 v1, VECTOR2 v2, VECTOR2 t, float r1 , float r2)
{
	if (sqrtf(cross(v1, v2, t)*cross(v1, v2, t)) / Length(v1, v2) <= r1 + r2)
	{
		return TRUE;
	}
	return FALSE;
}

//--------------------------------
//  あたり判定（三角）
//--------------------------------
BOOL TriangleHitCheck(VECTOR2 v1, VECTOR2 v2, VECTOR2 v3, VECTOR2 t, float r)
{
	if (sqrtf(cross(v1, v2, t)*cross(v1, v2, t)) / Length(v1, v2) <= r)
	{	
		if (dot(v1, v2, t)*dot2(v1, v2, t) <= 0) { return TRUE; }
	}
	if (sqrtf(cross(v2, v3, t)*cross(v2, v3, t)) / Length(v2, v3) <= r)
	{
		if (dot(v2, v3, t)*dot2(v2, v3, t) <= 0) { return TRUE; }
	}
	if (sqrtf(cross(v3, v1, t)*cross(v3, v1, t)) / Length(v3, v1) <= r)
	{
		if (dot(v3, v1, t)*dot2(v3, v1, t) <= 0) { return TRUE; }
	}
	if ((cross(v1, v2, t) > 0 && cross(v2, v3, t) > 0 && cross(v3, v1, t) > 0) || (cross(v1, v2, t) < 0 && cross(v2, v3, t) < 0 && cross(v3, v1, t) < 0))
	{
		return TRUE;
	}
	return FALSE;
}

//--------------------------------
//  あたり判定（四角）
//--------------------------------
BOOL SquareHitCheck(VECTOR2 v1, VECTOR2 v2, VECTOR2 v3, VECTOR2 v4, VECTOR2 t, float r)
{
	if (TriangleHitCheck(v1, v2, v3, t, r)) { return TRUE; }
	if (TriangleHitCheck(v1, v4, v3, t, r)) { return TRUE; }
    return FALSE;
}
BOOL SquareHitCheck(VECTOR2 v[4], VECTOR2 t, float r)
{
    return SquareHitCheck(v[0], v[1], v[2], v[3], t, r);
}


