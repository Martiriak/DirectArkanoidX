// Alessandro Pegoraro - Graphics Programming

#include "Vector2.h"
#include <cmath>
#include <cassert>
#include <DirectXMath.h>


Vector2& Vector2::operator+=(const Vector2& that)
{
	x += that.x;
	y += that.y;

	return *this;
}

Vector2& Vector2::operator+=(float scalar)
{
	x += scalar;
	y += scalar;

	return *this;
}


Vector2& Vector2::operator-=(float scalar)
{
	x -= scalar;
	y -= scalar;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& that)
{
	x -= that.x;
	y -= that.y;

	return *this;
}


Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}



Vector2 Vector2::getNormalized() const
{
	return *this / getLenght();
}

float Vector2::getLenght() const
{
	return std::sqrt(getSquaredLenght());
}


bool operator== (const Vector2& left_side, const Vector2& right_side)
{
	return DirectX::XMScalarNearEqual(left_side.x, right_side.x, 0.0000001f)
		&& DirectX::XMScalarNearEqual(left_side.y, right_side.y, 0.0000001f);
}

bool operator!= (const Vector2& left_side, const Vector2& right_side) { return !(left_side == right_side); }


float Vector2::dot(const Vector2& right_side, const Vector2& left_side)
{
	return (right_side.x * left_side.x) + (right_side.y * left_side.y);
}

Vector2 Vector2::lerp(const Vector2& right_side, const Vector2& left_side, float t)
{
	assert("Value t for lerping vectors2 isn't clamped between 0 and 1!" && t >= 0.f && t <= 1.f);

	return
	{
		right_side.x + t * (left_side.x - right_side.x),
		right_side.y + t * (left_side.y - right_side.y)
	};
}

Vector2 Vector2::reflect(const Vector2& to_reflect, Vector2 normal /*= up()*/)
{
	normal.normalize();

	return to_reflect - (2 * dot(to_reflect, normal) * normal);
}
