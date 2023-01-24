// Alessandro Pegoraro - Graphics Programming

#include "Vector2.h"
#include <cmath>


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


float Vector2::dot(const Vector2& right_side, const Vector2& left_side)
{
	return (right_side.x * left_side.x) + (right_side.y * left_side.y);
}
