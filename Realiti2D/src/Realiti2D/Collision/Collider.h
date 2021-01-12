#pragma once
#include "Realiti2D/Math/Math.h"

namespace Realiti2D {
	struct AABB {
		Vector2 MinPoint;
		Vector2 MaxPoint;
	};

	static bool CheckCollision(const AABB& RectA, const AABB& RectB);
}