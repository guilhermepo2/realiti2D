#include "Collider.h"

namespace Realiti2D {
	bool CheckCollision(const AABB& RectA, const AABB& RectB) {
		bool NotIntersect = RectA.MaxPoint.x < RectB.MinPoint.x ||
			RectA.MaxPoint.y < RectB.MinPoint.y ||
			RectB.MaxPoint.x < RectA.MinPoint.x ||
			RectB.MaxPoint.y < RectA.MinPoint.y;

		return !NotIntersect;
	}
}