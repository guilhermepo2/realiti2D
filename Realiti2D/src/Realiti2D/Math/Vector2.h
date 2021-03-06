#pragma once
#include <Math.h>

namespace Realiti2D {
	
	class Vector2 {
	public:
		float x;
		float y;

		Vector2() : x(0), y(0) {}
		Vector2(float InX, float InY) : x(InX), y(InY) {}
		Vector2(const Vector2& Other) : x(Other.x), y(Other.y) {}
		~Vector2() {}

	public:
		inline float Length() const { return sqrt( ( x * x) + ( y * y) ); }

		// Vector * Scalar
		template<typename T>
		Vector2 operator*(const T& Scalar) const {
			return Vector2(x * Scalar, y * Scalar);
		}

		// Vector / Scalar
		template<typename T>
		Vector2 operator/(const T& Scalar) const {
			return Vector2(x / Scalar, y / Scalar);
		}

		// Vector2 *= Scalar
		template<typename T>
		Vector2 operator*=(const T& Scalar) {
			x *= Scalar;
			y *= Scalar;
			return *this;
		}

		// Vector2 += Vector2
		Vector2 operator+=(const Vector2& Other) {
			x += Other.x;
			y += Other.y;
			return *this;
		}

		// Vector2 + Vector2
		friend Vector2 operator+(const Vector2& a, const Vector2& b) {
			return Vector2(a.x + b.x, a.y + b.y);
		}

		// Vector2 - Vector2
		friend Vector2 operator-(const Vector2& a, const Vector2& b) {
			return Vector2(a.x - b.x, a.y - b.y);
		}

	public:
		static const Vector2 Zero;
	};

	
}