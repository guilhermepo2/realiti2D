#pragma once


namespace Realiti2D {
	
	class Vector2 {
	public:
		float x;
		float y;

		Vector2() : x(0), y(0) {}
		Vector2(float InX, float InY) : x(InX), y(InY) {}
		Vector2(const Vector2& Other) : x(Other.x), y(Other.y) {}
		~Vector2() {}
	};

}