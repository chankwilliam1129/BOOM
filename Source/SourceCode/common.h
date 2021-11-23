#ifndef INCLUDED_COMMON
#define	INCLUDED_COMMON

#include <DirectXMath.h>

static float(*const ToRadian)(float) = DirectX::XMConvertToRadians;  // 角度をラジアンに
static float(*const ToDegree)(float) = DirectX::XMConvertToDegrees;  // ラジアンを角度に

#endif // !INCLUDED_COMMON
