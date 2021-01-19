#pragma once
#include "Realiti2D/Math/Math.h"

namespace Realiti2D {
	struct AABB {
		Vector2 MinPoint;
		Vector2 MaxPoint;
	};

	static bool CheckCollision(const AABB& RectA, const AABB& RectB) {
		bool NotIntersect =
			RectA.MaxPoint.x < RectB.MinPoint.x ||
			RectA.MaxPoint.y < RectB.MinPoint.y ||
			RectB.MaxPoint.x < RectA.MinPoint.x ||
			RectB.MaxPoint.y < RectA.MinPoint.y;

		return !NotIntersect;
	}
}