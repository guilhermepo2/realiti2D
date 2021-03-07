#pragma once
#include "Realiti2D/Math/Math.h"

namespace Realiti2D {

	struct LineSegment {
		LineSegment(const Vector2& Start, const Vector2& End) : m_Start(Start), m_End(End) {}
		Vector2 PointOnSegment(float t) const {
			return m_Start + (m_End - m_Start) * t;
		}

		Vector2 m_Start;
		Vector2 m_End;
	};

}