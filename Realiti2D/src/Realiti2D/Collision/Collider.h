#pragma once
#include "Realiti2D/Math/Math.h"
#include "LineSegment.h"

namespace Realiti2D {
	struct AABB {
		Vector2 MinPoint;
		Vector2 MaxPoint;

	public:
		bool Contains(const Vector2& point) const {
			bool bIsOutside = point.x < MinPoint.x ||
				point.y < MinPoint.y ||
				point.x > MaxPoint.x ||
				point.y > MaxPoint.y;

			return !bIsOutside;
		}
	};

	static bool CheckCollision(const AABB& RectA, const AABB& RectB) {
		bool NotIntersect =
			RectA.MaxPoint.x < RectB.MinPoint.x ||
			RectA.MaxPoint.y < RectB.MinPoint.y ||
			RectB.MaxPoint.x < RectA.MinPoint.x ||
			RectB.MaxPoint.y < RectA.MinPoint.y;

		return !NotIntersect;
	}

	static bool CheckLineCollision(const LineSegment& l, const AABB& Rect, float& outT) {
		/*
		DEBUG_INFO(
			"Checking Line Collision: l: ( Start: ({0}, {1}), End: ({2}, {3}) ) - AABB: ( Min: ({4}, {5}), Max: ({6}, {7}) )",
			l.m_Start.x, l.m_Start.y, l.m_End.x, l.m_End.y,
			Rect.MinPoint.x, Rect.MinPoint.y, Rect.MaxPoint.x, Rect.MaxPoint.y
		);
		*/

		float steps = 0.1f;
		
		for (float i = 0; i <= 1.0f; i += steps) {
			if (Rect.Contains(l.PointOnSegment(i))) {
				
				// DEBUG_INFO("Collided with t: {0}", i);

				outT = i;
				return true;
			}
		}

		return false;
	}
}