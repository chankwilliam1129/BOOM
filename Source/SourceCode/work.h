#ifndef INCLUDED_WORK
#define INCLUDED_WORK

#ifdef WORK
#define	EXTERN
#else
#define	EXTERN	extern
#endif // WORK


VECTOR2 NorVector(VECTOR2 a, VECTOR2 b);
VECTOR2 NorVector(VECTOR2 a);
VECTOR2 VecRotation(VECTOR2 a, float b);
bool areaCheck(VECTOR2 obj, int x1, int y1, int x2, int y2);
bool hit_check(VECTOR2 a, VECTOR2 b, float sum_radius);

#endif// !INCLUDED_WORK