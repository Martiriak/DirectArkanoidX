// Alessandro Pegoraro - Graphics Programming

#pragma once
#include <functional>


struct Vector2 final
{
	float x, y;


	inline explicit Vector2() : Vector2(0.f) { }
	inline explicit Vector2(float uniform) : x(uniform), y(uniform) { }
	inline Vector2(float _x, float _y) : x(_x), y(_y) { }


	Vector2& operator+= (const Vector2& that);
	Vector2& operator+= (float scalar);

	Vector2& operator-= (const Vector2& that);
	Vector2& operator-= (float scalar);

	Vector2& operator*= (float scalar);
	Vector2& operator/= (float scalar);

	inline Vector2 operator- () const { return Vector2(-x, -y); }


	Vector2 getNormalized() const;
	inline Vector2& normalize() { return *this = getNormalized(); }

	float getLenght() const;
	inline float getSquaredLenght() const { return dot(*this, *this); }


	friend bool operator== (const Vector2& left_side, const Vector2& right_side);
	friend bool operator!= (const Vector2& left_side, const Vector2& right_side);


	static inline Vector2 zero() { return Vector2(0.f); }
	static inline Vector2 one() { return Vector2(1.f); }
	static inline Vector2 right() { return Vector2(1.f, 0.f); }
	static inline Vector2 up() { return Vector2(0.f, 1.f); }

	static float dot(const Vector2& right_side, const Vector2& left_side);
	static Vector2 lerp(const Vector2& right_side, const Vector2& left_side, float t);
	static Vector2 reflect(const Vector2& to_reflect, Vector2 normal = up());
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



inline float operator* (const Vector2& right_side, const Vector2& left_side)
{
	return Vector2::dot(right_side, left_side);
}





namespace std
{
	template<>
	struct hash<Vector2>
	{
		size_t operator() (const Vector2& input) const noexcept
		{
			hash<float> float_hasher = {};

			size_t h1 = float_hasher(input.x);
			size_t h2 = float_hasher(input.y);

			return h1 ^ (h2 << 1);
		}
	};
}
