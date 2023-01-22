// Alessandro Pegoraro - Graphics Programming

#pragma once


struct Vector2 final
{
	float x, y;


	inline Vector2() : Vector2(0.f) { }
	inline Vector2(float uniform) : x(uniform), y(uniform) { }
	inline Vector2(float _x, float _y) : x(_x), y(_y) { }


	Vector2& operator+= (const Vector2& that);
	Vector2& operator+= (float scalar);

	Vector2& operator-= (const Vector2& that);
	Vector2& operator-= (float scalar);

	Vector2& operator*= (float scalar);
	Vector2& operator/= (float scalar);

	inline Vector2 operator- () const { return Vector2(-x, -y); }


	static inline Vector2 zero() { return Vector2(0.f); }
	static inline Vector2 one() { return Vector2(1.f); }
	static inline Vector2 right() { return Vector2(1.f, 0.f); }
	static inline Vector2 up() { return Vector2(0.f, 1.f); }

	static Vector2 dot(const Vector2& right_side, const Vector2& left_side);
};




inline Vector2 operator+ (const Vector2& right_side, const Vector2& left_side)
{
	return Vector2(right_side) += left_side;
}

inline Vector2 operator- (const Vector2& right_side, const Vector2& left_side)
{
	return Vector2(right_side) -= left_side;
}



inline Vector2 operator+ (const Vector2& vector, float scalar)
{
	return Vector2(vector) += scalar;
}
inline Vector2 operator+ (float scalar, const Vector2& vector) { return vector + scalar; }


inline Vector2 operator- (const Vector2& vector, float scalar)
{
	return Vector2(vector) -= scalar;
}
inline Vector2 operator- (float scalar, const Vector2& vector) { return vector - scalar; }



inline Vector2 operator* (const Vector2& vector, float scalar)
{
	return Vector2(vector) *= scalar;
}
inline Vector2 operator* (float scalar, const Vector2& vector) { return vector * scalar; }


inline Vector2 operator/ (const Vector2& vector, float scalar)
{
	return Vector2(vector) /= scalar;
}



inline Vector2 operator* (const Vector2& right_side, const Vector2& left_side)
{
	return Vector2::dot(right_side, left_side);
}
