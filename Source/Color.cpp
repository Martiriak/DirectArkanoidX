// Alessandro Pegoraro - Graphics Programming

#include "Color.h"
#include <cassert>


Color Color::lerp(const Color& right_side, const Color& left_side, float t)
{
	assert("Value t for lerping colors isn't clamped between 0 and 1!" && t >= 0.f && t <= 1.f);

	return
	{
		(byte)(right_side.r + (byte)(t * (left_side.r - right_side.r))),
		(byte)(right_side.g + (byte)(t * (left_side.g - right_side.g))),
		(byte)(right_side.b + (byte)(t * (left_side.b - right_side.b))),
		(byte)(right_side.a + (byte)(t * (left_side.a - right_side.a)))
	};
}
